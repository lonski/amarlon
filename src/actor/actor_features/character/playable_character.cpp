#include "playable_character.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <experience_table.h>
#include <race.h>
#include <inventory.h>
#include <actor_descriptions.h>
#include <character_class.h>
#include <spell_book.h>
#include <engine.h>
#include <spell_db.h>
#include <spell.h>

namespace amarlon {

PlayableCharacter::PlayableCharacter()
{
}

PlayableCharacter::PlayableCharacter(DescriptionPtr dsc)
  : Character(dsc)
{
  PlayableCharacterDescriptionPtr pcDsc = std::dynamic_pointer_cast<PlayableCharacterDescription>(dsc);
  if ( pcDsc != nullptr )
  {
    setHitPoints( pcDsc->hitPoints );
    setMaxHitPoints( pcDsc->maxHitPoints );
    setLevel( pcDsc->level );
    _abilityScores = pcDsc->abilityScores;
  }
}

PlayableCharacter::~PlayableCharacter()
{
}

ActorFeaturePtr PlayableCharacter::clone()
{
  auto* c = new PlayableCharacter(*this);
  cloneBase(c);
  return ActorFeaturePtr( c );
}

bool PlayableCharacter::isEqual(ActorFeaturePtr rhs) const
{  
  bool equal = false;
  PlayableCharacterPtr crhs = std::dynamic_pointer_cast<PlayableCharacter>(rhs);

  if (crhs != nullptr)
  {
    equal = Character::isEqual( rhs );
    equal &= std::equal(_abilityScores.begin(), _abilityScores.end(), crhs->_abilityScores.begin());
  }

  return equal;
}

CarryingCapacity::LoadLevel PlayableCharacter::getLoadLevel()
{
  CarryingCapacity::Data cData = CarryingCapacity::get(getAbilityScore(AbilityScore::STR), getRace()->getType() );
  return getEquipmentWeight() >= cData.heavy ? CarryingCapacity::LoadLevel::Heavy : CarryingCapacity::LoadLevel::Light;
}

int PlayableCharacter::calculateLoadPenalty()
{
  return getLoadLevel() == CarryingCapacity::LoadLevel::Heavy ? CarryingCapacity::HEAVY_LOAD_SPEED_PENALTY : 0;
}

int PlayableCharacter::getBaseAttackBonus()
{
  int base = AttackBonus::get(getClass()->getType(), getLevel());

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::AttackBonus; } );

  return it != _modifiers.end() ? base + it->Value : base;
}

int PlayableCharacter::getMeleeAttackBonus()
{
  return getBaseAttackBonus() + getModifier(AbilityScore::STR);
}

int PlayableCharacter::getMissileAttackBonus()
{
  int base = getBaseAttackBonus() + getModifier(AbilityScore::DEX);

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::MissileAttackBonus; } );

  return it != _modifiers.end() ? base + it->Value : base;
}

Damage PlayableCharacter::getDamage()
{
  Damage damage;

  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    damage = weapon->getDamage();
  }
  damage.value += getModifier( AbilityScore::STR );

  return damage;
}

int PlayableCharacter::modifyExperience(int modifier)
{
  modifier = Character::modifyExperience(modifier);

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event( (modifier > 0 ? EventId::Actor_ExperienceGained : EventId::Actor_ExperienceLost),
                         { {"value", std::to_string(std::abs(modifier))} } ));
  }

  if ( getLevel() < Experience::MAX_LEVEL )
  {
    LevelData data = Experience::getLevelData(getClass()->getType(), getLevel() + 1);
    if ( data.expNeeded != 0 && getExperience() >= data.expNeeded)
    {
      advanceLevel(data);

      ActorPtr actor = getOwner().lock();
      if ( actor )
      {
        actor->notify(Event(EventId::Actor_LeveledUp));
      }

      //TODO: maybe popup some window or advance te level manually like BG/NWN?
    }
  }

  return modifier;
}

void PlayableCharacter::advanceLevel()
{
  advanceLevel( Experience::getLevelData(getClass()->getType(), getLevel() + 1) );
}

void PlayableCharacter::advanceLevel(LevelData data)
{
  setLevel( getLevel() + 1 );

  int hpBonus =  static_cast<int>( data.hitDice ); //always maximum hp
      hpBonus += data.hpBonus;
      hpBonus += data.applyConModifier ? getModifier(AbilityScore::CON) : 0;

  setMaxHitPoints( getMaxHitPoints() + std::max(hpBonus, 1) );
  modifyHitPoints( hpBonus );

  //Add new spell slots
  if ( !data.spellSlotCount.empty() )
  {
    SpellBookPtr sb = getSpellBook();
    for ( const auto& pair : data.spellSlotCount )
    {
      int slotCount = sb->getSlotCount( pair.first );

      //New spell level reached
      if ( slotCount == 0 && pair.second > 0 && getClass()->getType() == CharacterClassType::Cleric )
      {
         sb->addKnownSpells(getClass()->getType(), pair.first );
      }

      //Insert the slots
      while ( slotCount < pair.second )
      {
        sb->addSlot( new SpellSlot( pair.first ) );
        ++slotCount;
      }
    }
  }

}

int PlayableCharacter::getSpeed()
{
  return std::max( Character::getSpeed() - calculateLoadPenalty(), 1 );
}

int PlayableCharacter::getEquipmentWeight()
{
  int weight = 0;

  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    weight += calculateInventoryItemsWeight();
    weight += calculateWearedItemsWeight();
  }

  return weight;
}

int PlayableCharacter::calculateInventoryItemsWeight()
{
  int weight = 0;

  InventoryPtr inventory = getOwner().lock()->getFeature<Inventory>();
  if ( inventory )
  {
    for ( ActorPtr i : inventory->items() )
    {
      weight += i->getFeature<Pickable>()->getWeight();
    }
  }

  return weight;
}

int PlayableCharacter::calculateWearedItemsWeight()
{
  int weight = 0;

  WearerPtr wearer = getOwner().lock()->getFeature<Wearer>();
  if ( wearer )
  {
    for ( auto slot : ItemSlotType() )
    {
      ActorPtr item = wearer->equipped(slot);
      if ( item )
      {
        weight = item->getFeature<Pickable>()->getWeight();
      }
    }
  }

  return weight;
}

int PlayableCharacter::getAbilityScore(AbilityScore::Type as)
{
  return _abilityScores[ as ];
}

bool PlayableCharacter::abilityRoll(AbilityScore::Type as, int extraModifier)
{
  int roll = dices::roll(dices::D20);
  if ( roll != dices::NATURAL_ONE )
  {
    int base = roll + getModifier(as) + extraModifier;
    return  roll == dices::NATURAL_TWENTY || base >= AbilityScore::getAbilityRollTarget( getLevel() );
  }
  return false;
}

int PlayableCharacter::getModifier(AbilityScore::Type as)
{
  return AbilityScore::getModifier( getAbilityScore(as) );
}

}

