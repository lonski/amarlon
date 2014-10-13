#include "destrucible.h"
#include "Actor/actor.h"
#include "Gui/gui.h"

Destrucible::Destrucible(float maxHp)
  : _owner(nullptr)
  , _maxHp(maxHp)
  , _hp(maxHp)
{
}

void Destrucible::setOwner(Actor *owner)
{
  _owner = owner;
}

bool Destrucible::isAlive() const
{
  return (_hp > 0);
}

void Destrucible::takeDamage(float power)
{
  _hp -= power;

  if ( _hp <= 0 )
    die();
}

void Destrucible::die()
{
  if (_owner)
  {
    Gui::Root.message( _owner->getName() + " dies.", TCODColor::darkRed );
    _owner->morph(ActorType::Corpse);
  }
}
