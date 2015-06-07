#include "pickable.h"
#include <iostream>
#include "actor/actor.h"
#include "actor/effects/effect.h"
#include "gui/gui.h"
#include "amarlon_except.h"

namespace amarlon {

const ActorFeature::Type Pickable::featureType = ActorFeature::PICKABLE;

Pickable::Pickable(bool stackable, int amount)
  : _stackable(stackable)
  , _amount(amount)
  , _effect(nullptr)
  , _damageDie(dices::NoDie)
  , _armorClass(0)
  , _weight(0)
  , _price(0)
{
}

Pickable::~Pickable()
{
  delete _effect;
}

PickablePtr Pickable::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  PickableDescriptionPtr pDsc = std::dynamic_pointer_cast<PickableDescription>(dsc);
  PickablePtr pickable = nullptr;

  if ( pDsc != nullptr )
  {
    pickable.reset( new Pickable(pDsc->stackable, pDsc->amount) );
    pickable->_itemSlot = pDsc->itemSlot;
    pickable->_category = pDsc->category;
    pickable->_damageDie = pDsc->damageDie;
    pickable->_armorClass = pDsc->armorClass;
    pickable->_weight = pDsc->weight;
    pickable->_price = pDsc->price;

    Effect* effect = Effect::create(pDsc->effect);
    pickable->setEffect(effect);
  }else throw creation_error("Wrong pickable description!");

  return pickable;
}

ActorPtr Pickable::spilt(int amount)
{
  ActorPtr r = ActorPtr(getOwner().lock());

  if ( isStackable() && amount < _amount && amount > 0 )
  {
    setAmount(_amount - amount);

    assert( _amount > 0 );
    assert( amount > 0 );

    r = getOwner().lock()->clone();
    r->getFeature<Pickable>()->setAmount(amount);
  }

  return r;
}

ActorFeaturePtr Pickable::clone()
{
  PickablePtr cloned( new Pickable(isStackable(), getAmount()) );
  cloned->setEffect( _effect ? _effect->clone() : nullptr );

  cloned->_itemSlot = _itemSlot;
  cloned->_category = _category;
  cloned->_damageDie = _damageDie;
  cloned->_armorClass = _armorClass;
  cloned->_weight = _weight;
  cloned->_price = _price;

  return cloned;
}

bool Pickable::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  PickablePtr crhs = std::dynamic_pointer_cast<Pickable>(rhs);

  if (crhs != nullptr)
  {
    equal = (_stackable == crhs->_stackable);
    equal &= (_damageDie == crhs->_damageDie);
    equal &= (_armorClass == crhs->_armorClass);
    equal &= (_weight == crhs->_weight);
    equal &= (_price == crhs->_price);
    //equal &= (_amount == crhs->_amount);  no amount comparing
    if ( getEffect() ) equal &= (getEffect()->isEqual( crhs->getEffect() ));
  }

  return equal;
}

bool Pickable::use(ActorPtr executor, std::vector<ActorPtr> targets)
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

dices::Die Pickable::getDamageDie() const
{
  return _damageDie;
}

int Pickable::getArmorClass() const
{
  return _armorClass;
}

int Pickable::getWeight() const
{
  return _weight;
}

int Pickable::getPrice() const
{
  return _price;
}

int Pickable::getAmount() const
{
  return _amount;
}

void Pickable::setAmount(int amount)
{
  _amount = amount;
}

}
