#include "playable_character.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>

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

int PlayableCharacter::getMeleeAttackBonus()
{
  return AttackBonusTable::getBonus(getClass(), getLevel()) + getModifier(AbilityScore::STR);
}

int PlayableCharacter::rollMeleeDamage()
{
  int dmg = getModifier( AbilityScore::STR );

  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    dmg += dices::roll( weapon->getDamageDie() );
  }

  return dmg < 1 ? 1 : dmg; //always minimum 1 dmg inflicted
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
