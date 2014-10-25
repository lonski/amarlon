#include "Pickable.h"
#include "Actor/Actor.h"
#include "Actor/Effects/Effect.h"
#include "Gui/Gui.h"
#include <iostream>

namespace amarlon {

Pickable::Pickable(bool stackable, int amount)
  : _stackable(stackable)
  , _amount(amount)
  , _effect(nullptr)
{
}

Pickable *Pickable::create(const PickableDescription &dsc)
{
  Pickable* pickable = new Pickable(dsc.stackable, dsc.amount);

  Effect* effect = Effect::create(dsc.effect);
  pickable->setEffect(effect);

  return pickable;
}

Actor* Pickable::spilt(int amount)
{
  Actor* r = _owner;

  if ( isStackable() && amount < _amount && amount > 0 )
  {
    setAmount(_amount - amount);

    assert( _amount > 0 );
    assert( amount > 0 );

    r = _owner->clone();
    r->afPickable()->setAmount(amount);    
  }

  return r;
}

ActorFeature *Pickable::clone()
{
  Pickable* cloned = new Pickable(isStackable(), getAmount());
  cloned->setEffect( _effect ? _effect->clone() : nullptr );

  return cloned;
}

bool Pickable::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  Pickable* crhs = dynamic_cast<Pickable*>(rhs);

  if (crhs)
  {
    equal = (_stackable == crhs->_stackable);
    //equal &= (_amount == crhs->_amount);  no amount comparing
    if ( getEffect() ) equal &= (getEffect()->isEqual( crhs->getEffect() ));
  }

  return equal;
}

bool Pickable::use(Actor* executor, std::vector<Actor*> targets)
{
  bool r = false;

  if (_effect != nullptr)
  {    
    r = _effect->apply(executor, targets);
  }

  return r;
}

int Pickable::getUsesCount() const
{
  if (_effect)
    return _effect->getUsesCount();

  return 0;
}

bool Pickable::isStackable() const
{
  return _stackable;
}
Effect *Pickable::getEffect() const
{
  return _effect;
}

void Pickable::setEffect(Effect *effect)
{
  _effect = effect;
}

int Pickable::getAmount() const
{
  return _amount;
}

void Pickable::setAmount(int amount)
{
  _amount = amount;
}

void Pickable::incAmount(int inc)
{
  _amount += inc;
}

}
