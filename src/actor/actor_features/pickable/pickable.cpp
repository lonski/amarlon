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

const ActorFeature::Type Pickable::FeatureType = ActorFeature::PICKABLE;

PickablePtr Pickable::create(const PickableData& data)
{
  PickablePtr p;

  switch( static_cast<PickableCategory>(data.item_type().category()) )
  {
    case PickableCategory::Scroll: p.reset( new Scroll  (data) ); break;
    default:                       p.reset( new Pickable(data) ); break;
  }

  return p;
}

Pickable::Pickable()
{
}

Pickable::Pickable(const Pickable &rhs)
{
  *this = rhs;
}

Pickable::~Pickable()
{
}

bool Pickable::operator==(const Pickable& rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Pickable& Pickable::operator=(const Pickable& rhs)
{
  if ( this != &rhs )
  {
    _data.CopyFrom(rhs._data);
  }
  return *this;
}

const PickableData &Pickable::getData() const
{
  return _data;
}

const google::protobuf::Message& Pickable::getDataPolymorphic() const
{
  return getData();
}

Pickable::Pickable(const PickableData& data)
{
  _data.CopyFrom(data);
}

ActorPtr Pickable::spilt(int amount)
{
  ActorPtr r = ActorPtr(getOwner().lock());

  if ( isStackable() && amount < getAmount() && amount > 0 )
  {
    setAmount(getAmount() - amount);

    r = getOwner().lock()->clone();
    r->getFeature<Pickable>()->setAmount(amount);
  }

  return r;
}

TargetType Pickable::getTargetType() const
{
  return static_cast<TargetType>(_data.target_type());
}

int Pickable::getRange() const
{
  return _data.range();
}

int Pickable::getRadius() const
{
  return _data.radius();
}

int Pickable::getScriptId() const
{
  return _data.script_id();
}

bool Pickable::use(ActorPtr executor, const Target& target)
{
  bool r = false;

  if ( getUsesCount() != 0 )
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

        if( r ) _data.set_uses_count( getUsesCount() - 1);
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
  return getScriptId() != 0 && getUsesCount() !=0;
}

int Pickable::getUsesCount() const
{
  return _data.uses_count();
}

bool Pickable::isStackable() const
{
  return _data.stackable();
}

ItemSlotType Pickable::getItemSlot() const
{
  return static_cast<ItemSlotType>(_data.item_slot());
}

void Pickable::setItemSlot(const ItemSlotType &itemSlot)
{
  _data.set_item_slot( static_cast<int>(itemSlot) );
}

bool Pickable::isEquippable()
{
  return ( getItemSlot() != ItemSlotType::Null );
}

PickableCategory Pickable::getCategory() const
{
  return static_cast<PickableCategory>(_data.item_type().category());
}

void Pickable::setCategory(PickableCategory category)
{
  _data.mutable_item_type()->set_category( static_cast<int>(category) );
}

ItemType Pickable::getItemType() const
{
  return ItemType(_data.item_type());
}

void Pickable::setItemType(ItemType type)
{
  _data.mutable_item_type()->CopyFrom(type.getData());
}

Damage Pickable::getDamage() const
{
  return Damage(_data.damage() );
}

int Pickable::getArmorClass() const
{
  return _data.armor_class();
}

int Pickable::getWeight() const
{
  return _data.weight();
}

int Pickable::getPrice() const
{
  return _data.price();
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

  Damage dmg = getDamage();
  if ( dmg != Damage() )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Damage: " +
                                                        toStr(dmg.diceCount) + "d" +
                                                        toStr(static_cast<int>(dmg.dice) );
    if ( dmg.value != 0 )
    {
      str += ( dmg.value >0 ? "+" : "-" ) + toStr(dmg.value);
    }

    str += "#";
  }
  if ( getArmorClass() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Armor class: " + toStr(getArmorClass()) + "#";
  }
  if ( getRange() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Range: " + toStr(getRange()) + "#";
  }
  if ( getRadius() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Radius: " + toStr(getRadius()) + "#";
  }

  return str;
}

std::string Pickable::getScriptPath() const
{
  return "scripts/items/" + std::to_string( static_cast<int>( getScriptId() ) ) + ".lua";
}

int Pickable::getAmount() const
{
  return _data.amount();
}

void Pickable::setAmount(int amount)
{
  _data.set_amount(amount);
}

}

