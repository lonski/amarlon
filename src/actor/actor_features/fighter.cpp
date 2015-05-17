#include "fighter.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <actor.h>
#include <gui.h>
#include <utils.h>
#include <messenger.h>
#include <amarlon_except.h>
#include <engine.h>
#include <map.h>

namespace amarlon {

const ActorFeature::Type Fighter::featureType = ActorFeature::FIGHTER;

Fighter::Fighter(float power, float maxHp)
  : _power(power)
  , _maxHp(maxHp)
  , _hp(maxHp)
{
}

FighterPtr Fighter::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  FighterPtr fighter = nullptr;
  FighterDescriptionPtr fighterDsc = std::dynamic_pointer_cast<FighterDescription>(dsc);

  if ( fighterDsc != nullptr )
  {
    fighter.reset( new Fighter(fighterDsc->power, fighterDsc->maxHp) );
  }else throw creation_error("Wrong fighter description!");

  return fighter;
}

ActorFeaturePtr Fighter::clone()
{
  FighterPtr cloned( new Fighter(_power, _maxHp) );
  return cloned;
}

bool Fighter::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  FighterPtr crhs = std::dynamic_pointer_cast<Fighter>(rhs);

  if (crhs != nullptr)
  {
    equal = (_power == crhs->_power);
    equal &= (_maxHp == crhs->_maxHp);
  }

  return equal;
}

void Fighter::attack(ActorPtr enemy)
{
  if ( enemy->isAlive() )
  {
    Messenger::message()->actorHit( ActorPtr(getOwner()), enemy, _power);

    enemy->getFeature<Fighter>()->takeDamage(_power);
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
  if (getOwner())
  {
    Messenger::message()->actorDies( ActorPtr(getOwner()) );
    getOwner()->morph(ActorType::Corpse);
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

void Fighter::setHp(float hp)
{
  _hp = hp;
}

float Fighter::getMaxHp() const
{
  return _maxHp;
}

void Fighter::setMaxHp(float maxHp)
{
  _maxHp = maxHp;
}

float Fighter::getPower() const
{
  return _power;
}

void Fighter::setPower(float power)
{
  _power = power;
}

}
