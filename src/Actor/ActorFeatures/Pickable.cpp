#include "Pickable.h"
#include "Actor/Actor.h"
#include "Actor/Effects/Effect.h"
#include "gui/gui.h"
#include <amarlon_except.h>
#include <iostream>

namespace amarlon {

const ActorFeature::Type Pickable::featureType = ActorFeature::PICKABLE;

Pickable::Pickable(bool stackable, int amount)
  : _stackable(stackable)
  , _amount(amount)
  , _effect(nullptr)
{
}

Pickable::~Pickable()
{
  delete _effect;
}

Pickable *Pickable::create(Description *dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  PickableDescription* pDsc = dynamic_cast<PickableDescription*>(dsc);
  Pickable* pickable = nullptr;

  if ( pDsc != nullptr )
  {
    pickable = new Pickable(pDsc->stackable, pDsc->amount);
    pickable->_itemSlot = pDsc->itemSlot;
    pickable->_category = pDsc->category;

    Effect* effect = Effect::create(pDsc->effect);
    pickable->setEffect(effect);
  }else throw creation_error("Wrong pickable description!");

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
    r->getFeature<Pickable>()->setAmount(amount);
  }

  return r;
}

ActorFeature *Pickable::clone()
{
  Pickable* cloned = new Pickable(isStackable(), getAmount());
  cloned->setEffect( _effect ? _effect->clone() : nullptr );

  cloned->_itemSlot = _itemSlot;
  cloned->_category = _category;

  return cloned;
}

bool Pickable::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  Pickable* crhs = dynamic_cast<Pickable*>(rhs);

  if (crhs != nullptr)
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
ItemSlotType Pickable::getItemSlot() const
{
  return _itemSlot;
}

void Pickable::setItemSlot(const ItemSlotType &itemSlot)
{
  _itemSlot = itemSlot;
}

bool Pickable::isEquippable()
{
  return ( _itemSlot != ItemSlotType::Null );
}

PickableCategory Pickable::getCategory() const
{
  return _category;
}

void Pickable::setCategory(const PickableCategory &category)
{
  _category = category;
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

void Pickable::decAmount(int dec)
{
  _amount -= dec;
}

}
