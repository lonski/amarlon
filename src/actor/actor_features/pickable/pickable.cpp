#include "pickable.h"
#include <iostream>
#include <actor.h>
#include <effect.h>
#include <gui.h>
#include <amarlon_except.h>
#include <utils.h>
#include <actor_descriptions.h>
#include <cassert>

namespace amarlon {

const ActorFeature::Type Pickable::featureType = ActorFeature::PICKABLE;

Pickable::Pickable(bool stackable, int amount)
  : _stackable(stackable)
  , _amount(amount)
  , _armorClass(0)
  , _weight(0)
  , _price(0)
  , _usesCount(0)
  , _targetType(TargetType::SINGLE_NEIGHBOUR)
{
}

Pickable::~Pickable()
{
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
    pickable->_armorClass = pDsc->armorClass;
    pickable->_weight = pDsc->weight;
    pickable->_price = pDsc->price;
    pickable->_damage = pDsc->damage;
    pickable->_usesCount = pDsc->uses;
    pickable->_targetType = pDsc->targetType;
    pickable->setEffect( Effect::create(pDsc->effect) );
  }

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
  cloned->_damage = _damage;
  cloned->_armorClass = _armorClass;
  cloned->_weight = _weight;
  cloned->_price = _price;
  cloned->_usesCount = _usesCount;
  cloned->_targetType = _targetType;

  return cloned;
}

bool Pickable::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  PickablePtr crhs = std::dynamic_pointer_cast<Pickable>(rhs);

  if (crhs != nullptr)
  {
    equal = (_stackable == crhs->_stackable);
    equal &= (_armorClass == crhs->_armorClass);
    equal &= (_weight == crhs->_weight);
    equal &= (_price == crhs->_price);
    equal &= (_damage == crhs->_damage);
    equal &= (_targetType == crhs->_targetType);
    //equal &= _usesCount == crhs->_usesCount;
    //equal &= (_amount == crhs->_amount);  no amount comparing
    if ( getEffect() ) equal &= (getEffect()->isEqual( crhs->getEffect() ));
  }

  return equal;
}

TargetType Pickable::getTargetType() const
{
  return _targetType;
}

bool Pickable::use(ActorPtr executor, const Target& target)
{
  bool r = false;

  if ( _effect != nullptr && _usesCount != 0 )
  {
    if ( _effect->apply(executor, target) )
    {
      --_usesCount;
      r = true;
    }
  }

  return r;
}

int Pickable::getUsesCount() const
{
  return _usesCount;
}

bool Pickable::isStackable() const
{
  return _stackable;
}
EffectPtr Pickable::getEffect() const
{
  return _effect;
}

void Pickable::setEffect(EffectPtr effect)
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

Damage Pickable::getDamage() const
{
  return _damage;
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

std::string Pickable::getDescription()
{
  std::string str = colorToStr(TCODColor::darkerTurquoise, true) + "Category: " + PickableCategory2Str( getCategory() );

  if ( getItemSlot() != ItemSlotType::Null )
  {
    str += " (";
    str += ItemSlotType2Str( getItemSlot() ) ;
    str += ")";
  }
  str += "\n";
  str += colorToStr(TCODColor::darkerTurquoise, true) + "Weight: " + toStr( getWeight() ) + " lbs\n \n";

  if ( getDamage() != Damage() )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Damage: " +
                                                        toStr(_damage.diceCount) + "d" +
                                                        toStr(static_cast<int>(_damage.dice) );
    if ( _damage.value != 0 )
    {
      str += ( _damage.value >0 ? "+" : "-" ) + toStr(_damage.value);
    }

    str += "\n";
  }
  if ( getArmorClass() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Armor class: " + toStr(getArmorClass()) + "\n";
  }

  return str;
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

