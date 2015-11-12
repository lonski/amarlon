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
#include <scroll.h>

namespace amarlon {

const ActorFeature::Type Pickable::featureType = ActorFeature::PICKABLE;

Pickable::Pickable(bool stackable, int amount)
  : _usesCount(0)
  , _stackable(stackable)
  , _amount(amount)
  , _itemSlot(ItemSlotType::Null)
  , _armorClass(0)
  , _weight(0)
  , _price(0)
  , _targetType(TargetType::SINGLE_NEIGHBOUR)
  , _scriptId(0)
  , _range(0)
  , _radius(0)  
{
}

Pickable::Pickable(DescriptionPtr dsc)
{
  PickableDescriptionPtr pDsc = std::dynamic_pointer_cast<PickableDescription>(dsc);
  if ( pDsc != nullptr )
  {
    _stackable = pDsc->stackable;
    _amount = pDsc->amount;
    _itemSlot = pDsc->itemSlot;
    _armorClass = pDsc->armorClass;
    _weight = pDsc->weight;
    _price = pDsc->price;
    _damage = pDsc->damage;
    _usesCount = pDsc->uses;
    _targetType = pDsc->targetType;
    _scriptId = pDsc->scriptId;
    _type = pDsc->type;
    _range = pDsc->range;
    _radius = pDsc->radius;
  }
}

Pickable::~Pickable()
{
}

PickablePtr Pickable::create(DescriptionPtr dsc)
{
  PickablePtr p;

  PickableDescriptionPtr pDsc = std::dynamic_pointer_cast<PickableDescription>(dsc);
  if ( pDsc )
  {
    switch (pDsc->type.category)
    {
      case PickableCategory::Scroll: p.reset( new Scroll(pDsc) ); break;
      default : p.reset( new Pickable(dsc) );
    }
  }

  return p;
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
  PickablePtr cloned( new Pickable );

  clone( cloned.get() );

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

int Pickable::getRange() const
{
  return _range;
}

int Pickable::getRadius() const
{
  return _radius;
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

void Pickable::clone(Pickable *p)
{
  if ( p )
  {
    p->_stackable = _stackable;
    p->_amount = _amount;
    p->_itemSlot = _itemSlot;
    p->_damage = _damage;
    p->_armorClass = _armorClass;
    p->_weight = _weight;
    p->_price = _price;
    p->_usesCount = _usesCount;
    p->_targetType = _targetType;
    p->_itemSlot = _itemSlot;
    p->_scriptId = _scriptId;
    p->_type = _type;
  }
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

