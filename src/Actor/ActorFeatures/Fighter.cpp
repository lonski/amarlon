#include "Fighter.h"
#include "Actor/Actor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Gui/Gui.h"
#include "Utils/Utils.h"
#include "Utils/Messenger.h"

Fighter::Fighter(float power, float maxHp)
  : _power(power)
  , _maxHp(maxHp)
  , _hp(maxHp)
{
}

Fighter *Fighter::create(const FighterDescription &dsc)
{
  return new Fighter(dsc.power, dsc.maxHp);
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

  if (crhs)
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
