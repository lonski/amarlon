#include "pickable.h"
#include <iostream>
#include <actor.h>
#include <gui.h>
#include <amarlon_except.h>
#include <utils.h>
#include <actor_descriptions.h>
#include <cassert>
#include <lua_state.h>
#include <engine.h>
#include <cstdio>

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
  , _scriptId(0)
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
    pickable->_armorClass = pDsc->armorClass;
    pickable->_weight = pDsc->weight;
    pickable->_price = pDsc->price;
    pickable->_damage = pDsc->damage;
    pickable->_usesCount = pDsc->uses;
    pickable->_targetType = pDsc->targetType;
    pickable->_scriptId = pDsc->scriptId;
    pickable->_type = pDsc->type;
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

  cloned->_itemSlot = _itemSlot;
  cloned->_damage = _damage;
  cloned->_armorClass = _armorClass;
  cloned->_weight = _weight;
  cloned->_price = _price;
  cloned->_usesCount = _usesCount;
  cloned->_targetType = _targetType;
  cloned->_itemSlot = _itemSlot;
  cloned->_scriptId = _scriptId;
  cloned->_type = _type;

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
    equal &= (_itemSlot == crhs->_itemSlot);
    equal &= (_scriptId == crhs->_scriptId);
    equal &= (_type == crhs->_type);
  }

  return equal;
}

TargetType Pickable::getTargetType() const
{
  return _targetType;
}

int Pickable::getScriptId() const
{
  return _scriptId;
}

bool Pickable::use(ActorPtr executor, const Target& target)
{
  bool r = false;

  if ( _usesCount != 0 )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();

    if ( lua.execute( getScriptPath() ) )
    {
      try
      {
        r = luabind::call_function<bool>(
            lua()
          , "onUse"
          , executor
          , getOwner().lock()
          , &target
        );

        if( r ) --_usesCount;
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }
  }

  return r;
}

bool Pickable::isUsable() const
{
  return _scriptId != 0 && _usesCount !=0;
}

int Pickable::getUsesCount() const
{
  return _usesCount;
}

bool Pickable::isStackable() const
{
  return _stackable;
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
  return _type.category;
}

void Pickable::setCategory(PickableCategory category)
{
  _type.category = category;
}

ItemType Pickable::getItemType() const
{
  return _type;
}

void Pickable::setItemType(ItemType type)
{
  _type = type;
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
  str += "#";
  str += colorToStr(TCODColor::darkerTurquoise, true) + "Weight: " + toStr( getWeight() ) + " lbs# #";

  if ( getDamage() != Damage() )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Damage: " +
                                                        toStr(_damage.diceCount) + "d" +
                                                        toStr(static_cast<int>(_damage.dice) );
    if ( _damage.value != 0 )
    {
      str += ( _damage.value >0 ? "+" : "-" ) + toStr(_damage.value);
    }

    str += "#";
  }
  if ( getArmorClass() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Armor class: " + toStr(getArmorClass()) + "#";
  }

         return str;
  }

std::string Pickable::getScriptPath() const
{
  return "scripts/items/" + std::to_string( static_cast<int>(_scriptId) ) + ".lua";
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

