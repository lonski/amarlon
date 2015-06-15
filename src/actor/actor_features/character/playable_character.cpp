#include "playable_character.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <experience_table.h>
#include <messenger.h>
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

bool PlayableCharacter::isEqual(ActorFeaturePtr rhs)
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

int PlayableCharacter::getBaseAttackBonus()
{
  return attack_bonus_table::getBonus(getClass(), getLevel());
}

int PlayableCharacter::getMeleeAttackBonus()
{
  return attack_bonus_table::getBonus(getClass(), getLevel()) + getModifier(AbilityScore::STR);
}

int PlayableCharacter::rollMeleeDamage()
{
  int dmg = getModifier( AbilityScore::STR );

  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    dmg += dices::roll( weapon->getDamageDice(), weapon->getDiceCount() );
  }

  return std::max(dmg, 1); //always minimum 1 dmg inflicted
}

void PlayableCharacter::modifyExperience(int modifier)
{
  Character::modifyExperience(modifier);

  if ( getLevel() < experience_table::MAX_LEVEL )
  {
    LevelData data = experience_table::getLevelData(getClass(), getLevel() + 1);
    if ( data.expNeeded != 0 && getExperience() >= data.expNeeded)
    {
      advanceLevel(data);
    }
  }
}

void PlayableCharacter::advanceLevel(LevelData data)
{
  setLevel( getLevel() + 1 );

  int hpBonus =  dices::roll( data.hitDice );
      hpBonus += data.hpBonus;
      hpBonus += data.applyConModifier ? getModifier(AbilityScore::CON) : 0;

  setMaxHitPoints( getMaxHitPoints() + std::max(hpBonus, 1) );
  modifyHitPoints( hpBonus );

  Messenger::message()->actorLeveledUp(getOwner().lock(), getLevel());
  //TODO: maybe popup some window or advance te level manually like BG/NWN?
  //Apply the spell levels
}

int PlayableCharacter::getAbilityScore(AbilityScore::Type as)
{
  return _abilityScores[ as ];
}

int PlayableCharacter::getModifier(AbilityScore::Type as)
{
  return AbilityScore::getModifier( getAbilityScore(as) );
}

}
