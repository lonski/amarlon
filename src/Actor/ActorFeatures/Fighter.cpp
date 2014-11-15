#include "Fighter.h"
#include "Actor/Actor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "gui/gui.h"
#include <utils/utils.h>
#include <utils/messenger.h>
#include <amarlon_except.h>

namespace amarlon {

Fighter::Fighter(float power, float maxHp)
  : _power(power)
  , _maxHp(maxHp)
  , _hp(maxHp)
{
}

Fighter *Fighter::create(Description *dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  Fighter* fighter = nullptr;
  FighterDescription* fighterDsc = dynamic_cast<FighterDescription*>(dsc);

  if ( fighterDsc != nullptr )
  {
    fighter = new Fighter(fighterDsc->power, fighterDsc->maxHp);
  }else throw creation_error("Wrong fighter description!");

  return fighter;
}

ActorFeature *Fighter::clone()
{
  Fighter* cloned = new Fighter(_power, _maxHp);
  return cloned;
}

bool Fighter::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  Fighter* crhs = dynamic_cast<Fighter*>(rhs);

  if (crhs != nullptr)
  {
    equal = (_power == crhs->_power);
    equal &= (_maxHp == crhs->_maxHp);
  }

  return equal;
}

void Fighter::attack(Actor *enemy)
{
  if ( enemy->isAlive() )
  {
    Messenger::message()->actorHit(_owner, enemy, _power);

    enemy->afFighter()->takeDamage(_power);
  }
}

bool Fighter::isAlive() const
{
  return (_hp > 0);
}

void Fighter::takeDamage(float power)
{
  _hp -= power;

  if ( _hp <= 0 )
    die();
}

void Fighter::die()
{
  if (_owner)
  {
    Messenger::message()->actorDies(_owner);
    _owner->morph(ActorType::Corpse);
  }
}

int Fighter::heal(int hp)
{
  int healed = hp;

  _hp += hp;

  if ( _hp > _maxHp )
  {
    healed -= (_hp - _maxHp);
    _hp = _maxHp;
  }

  return healed;
}

float Fighter::getHp() const
{
  return _hp;
}

float Fighter::getMaxHp() const
{
  return _maxHp;
}

}
