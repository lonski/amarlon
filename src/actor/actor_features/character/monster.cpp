#include "monster.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <iostream>

namespace amarlon {

Monster::Monster(int level, int hitPointsBonus)
  : _damageDice(dices::D4)
  , _morale(0)  
  , _damageDiceCount(1)
{
  setLevel(level);
  setMaxHitPoints( dices::roll(dices::D8, getLevel() ) + hitPointsBonus );
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
    equal &= _damageDiceCount      == crhs->_damageDiceCount;
    equal &= _morale          == crhs->_morale;
  }

  return equal;
}

int Monster::getMeleeAttackBonus()
{
  return AttackBonusTable::getBonus(CharacterClass::MONSTER, getLevel() );
}

int Monster::rollMeleeDamage()
{  
  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    return dices::roll( weapon->getDamageDie() );
  }

  return dices::roll(_damageDice, _damageDiceCount);
}

int Monster::getMorale()
{
  return _morale;
}

}
