#include "pickable.h"
#include <iostream>
#include <actor.h>
#include <effect.h>
#include <gui.h>
#include <amarlon_except.h>
#include <utils.h>

namespace amarlon {

const ActorFeature::Type Pickable::featureType = ActorFeature::PICKABLE;

Pickable::Pickable(bool stackable, int amount)
  : _stackable(stackable)
  , _amount(amount)
  , _effect(nullptr)
  , _damageDice(dices::NoDice)
  , _diceCount(0)
  , _armorClass(0)
  , _weight(0)
  , _price(0)
  , _targetType(TargetType::SINGLE_NEIGHBOUR)
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
    pickable->_damageDice = pDsc->damageDice;
    pickable->_armorClass = pDsc->armorClass;
    pickable->_weight = pDsc->weight;
    pickable->_price = pDsc->price;
    pickable->_diceCount = pDsc->damageDiceCount;
    pickable->_usesCount = pDsc->uses;
    pickable->_targetType = pDsc->targetType;

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
  cloned->_damageDice = _damageDice;
  cloned->_diceCount = _diceCount;
  cloned->_armorClass = _armorClass;
  cloned->_weight = _weight;
  cloned->_price = _price;
  cloned->_usesCount = _usesCount;
  cloned->_targetType = _targetType;

  return cloned;
}

bool Pickable::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  PickablePtr crhs = std::dynamic_pointer_cast<Pickable>(rhs);

  if (crhs != nullptr)
  {
    equal = (_stackable == crhs->_stackable);
    equal &= (_damageDice == crhs->_damageDice);
    equal &= (_armorClass == crhs->_armorClass);
    equal &= (_weight == crhs->_weight);
    equal &= (_price == crhs->_price);
    equal &= (_diceCount == crhs->_diceCount);
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

dices::Dice Pickable::getDamageDice() const
{
  return _damageDice;
}

int Pickable::getDiceCount() const
{
  return _diceCount;
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

  if ( getDamageDice() != dices::NoDice )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Damage: " + toStr(getDiceCount()) + "d" + toStr(getDamageDice()) + "\n";
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
