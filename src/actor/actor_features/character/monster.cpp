#include "monster.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <iostream>
#include <utils.h>

namespace amarlon {

Monster::Monster(int level, int hitPointsBonus)
  : _damageDice(dices::D4)
  , _damageDiceCount(1)
  , _morale(0)  
  , _hpMod(hitPointsBonus)
{
  setLevel(level);
  setMaxHitPoints( std::max( dices::roll(dices::D8, getLevel() ) + _hpMod, 1 ) );
  setHitPoints( getMaxHitPoints() );
}

Monster::~Monster()
{
}

ActorFeaturePtr Monster::clone()
{
  return ActorFeaturePtr( new Monster(*this) );
}

bool Monster::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  MonsterPtr crhs = std::dynamic_pointer_cast<Monster>(rhs);

  if (crhs != nullptr)
  {
    equal = Character::isEqual( rhs );
    equal &= _damageDice      == crhs->_damageDice;
    equal &= _damageDiceCount == crhs->_damageDiceCount;
    equal &= _morale          == crhs->_morale;
  }

  return equal;
}

int Monster::getBaseAttackBonus()
{
  return getMeleeAttackBonus();
}

int Monster::getMeleeAttackBonus()
{
  return AttackBonus::get(CharacterClass::Monster, getLevel() );
}

int Monster::rollMeleeDamage()
{  
  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    return dices::roll( weapon->getDamageDice(), weapon->getDiceCount() );
  }

  return dices::roll(_damageDice, _damageDiceCount);
}

std::string Monster::getDescription()
{
  std::string str = Character::getDescription();

  str += colorToStr(TCODColor::darkTurquoise, true) + "Hit points dice: " + toStr( getLevel() ) + "d8" + ( _hpMod >= 0 ? "+" : "") + toStr(_hpMod);

  return str;
}

int Monster::getMorale()
{
  return _morale;
}

}
