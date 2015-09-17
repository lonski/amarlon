#include "playable_character.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <experience_table.h>

#include <inventory.h>
#include <actor_descriptions.h>

namespace amarlon {

PlayableCharacter::PlayableCharacter()
{
}

PlayableCharacter::~PlayableCharacter()
{
}

ActorFeaturePtr PlayableCharacter::clone()
{
  return ActorFeaturePtr( new PlayableCharacter(*this) );
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
  CarryingCapacity::Data cData = CarryingCapacity::get(getAbilityScore(AbilityScore::STR), getRace());
  return getEquipmentWeight() >= cData.heavy ? CarryingCapacity::LoadLevel::Heavy : CarryingCapacity::LoadLevel::Light;
}

int PlayableCharacter::calculateLoadPenalty()
{
  return getLoadLevel() == CarryingCapacity::LoadLevel::Heavy ? CarryingCapacity::HEAVY_LOAD_SPEED_PENALTY : 0;
}

int PlayableCharacter::getBaseAttackBonus()
{
  return AttackBonus::get(getClass(), getLevel());
}

int PlayableCharacter::getMeleeAttackBonus()
{
  return AttackBonus::get(getClass(), getLevel()) + getModifier(AbilityScore::STR);
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

void PlayableCharacter::modifyExperience(int modifier)
{
  Character::modifyExperience(modifier);

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event( (modifier > 0 ? EventId::Actor_ExperienceGained : EventId::Actor_ExperienceLost),
                         { {"value", std::to_string(std::abs(modifier))} } ));
  }

  if ( getLevel() < Experience::MAX_LEVEL )
  {
    LevelData data = Experience::getLevelData(getClass(), getLevel() + 1);
    if ( data.expNeeded != 0 && getExperience() >= data.expNeeded)
    {
      advanceLevel(data);
    }
  }
}

int PlayableCharacter::getSpeed()
{
  return std::max( Character::getSpeed() - calculateLoadPenalty(), 0 );
}

void PlayableCharacter::advanceLevel(LevelData data)
{
  setLevel( getLevel() + 1 );

  int hpBonus =  dices::roll( data.hitDice );
      hpBonus += data.hpBonus;
      hpBonus += data.applyConModifier ? getModifier(AbilityScore::CON) : 0;

  setMaxHitPoints( getMaxHitPoints() + std::max(hpBonus, 1) );
  modifyHitPoints( hpBonus );

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event(EventId::Actor_LeveledUp));
  }

  //TODO: maybe popup some window or advance te level manually like BG/NWN?
  //Apply the spell levels
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

int PlayableCharacter::getModifier(AbilityScore::Type as)
{
  return AbilityScore::getModifier( getAbilityScore(as) );
}

CharacterPtr PlayableCharacter::Creator::create(CharacterDescriptionPtr dsc)
{
  PlayableCharacterPtr pc = nullptr;

  PlayableCharacterDescriptionPtr pcDsc = std::dynamic_pointer_cast<PlayableCharacterDescription>(dsc);
  if ( pcDsc != nullptr )
  {
    pc = std::make_shared<PlayableCharacter>();

    pc->setHitPoints( pcDsc->hitPoints );
    pc->setMaxHitPoints( pcDsc->maxHitPoints );
    pc->setLevel( pcDsc->level );
    pc->_abilityScores = pcDsc->abilityScores;

    Character::Creator::fillCommonCharacterPart(pc, dsc);
  }

  return pc;
}

}
