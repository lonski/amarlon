#include "Pickable.h"
#include "Actor/Actor.h"
#include "Actor/Effects/Effect.h"
#include "Gui/Gui.h"
#include <iostream>

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
    r = new Actor( _owner->getId(), _owner->getX(), _owner->getY() );
    r->afPickable()->setAmount(amount);    
  }

  return r;
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

