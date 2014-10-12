#include "attacker.h"
#include "Actor/actor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Gui/gui.h"
#include "Utils/utils.h"

Attacker::Attacker(float power)
  : _owner(nullptr)
  , _power(power)
{
}

void Attacker::setOwner(Actor *owner)
{
  _owner = owner;
}

void Attacker::attack(Actor *enemy)
{
  if ( enemy->isAlive() )
  {
    std::string enemyName = enemy->getName() == "Player" ? "you" : enemy->getName();
    std::string atackerName = _owner->getName() == "Player" ? "You" : _owner->getName();

    float dmgDone = enemy->afDestrucible()->takeDamage(_power);

    Gui::Root.message(atackerName + " hit " + enemyName + " for " + to_stringp(dmgDone) + "hp!", TCODColor::red);
  }
}
