#include "Fighter.h"
#include "Actor/Actor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Gui/Gui.h"
#include "Utils/Utils.h"

Fighter::Fighter(float power, float maxHp)
  : _power(power)
  , _maxHp(maxHp)
  , _hp(maxHp)
{
}

void Fighter::attack(Actor *enemy)
{
  if ( enemy->isAlive() )
  {
    std::string enemyName = enemy->getName() == "Player" ? "you" : enemy->getName();
    std::string atackerName = _owner->getName() == "Player" ? "You" : _owner->getName();

    Gui::Root.message(atackerName + " hit " + enemyName + " for " + to_stringp(_power) + "hp!", TCODColor::red);
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
    Gui::Root.message( _owner->getName() + " dies.", TCODColor::darkRed );
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
