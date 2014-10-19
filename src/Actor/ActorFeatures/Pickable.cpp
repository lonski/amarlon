#include "Pickable.h"
#include "Actor/Actor.h"
#include <iostream>

Pickable::Pickable(bool stackable, int amount)
  : _stackable(stackable)
  , _amount(amount)
{
}

Actor* Pickable::spilt(int amount)
{
  Actor* r = _owner;

  if ( isStackable() && amount < _amount && amount > 0 )
  {
    setAmount(_amount - amount);
    r = new Actor( _owner->getId(), _owner->getX(), _owner->getY() );
    r->afPickable()->setAmount(amount);    
  }

  return r;
}

void Pickable::use(Actor*)
{
  //todo
}

bool Pickable::isStackable() const
{
  return _stackable;
}
int Pickable::getAmount() const
{
  return _amount;
}

void Pickable::setAmount(int amount)
{
  _amount = amount;
}

