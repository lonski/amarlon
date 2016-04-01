#include "wearer.h"
#include <algorithm>
#include <actor_container.h>
#include <actor.h>
#include <amarlon_except.h>

namespace amarlon {

const ActorFeature::Type Wearer::FeatureType = ActorFeature::WEARER;

WearerPtr Wearer::create(const WearerData &data)
{
  return WearerPtr( new Wearer(data) );
}

Wearer::Wearer()
  : _equippedItems( new ActorContainer )
{
}

Wearer::Wearer(const Wearer& rhs)
{
  *this = rhs;
}

Wearer::~Wearer()
{
}

bool Wearer::operator==(const Wearer &rhs) const
{
  updateData();
  rhs.updateData();
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Wearer& Wearer::operator=(const Wearer& rhs)
{
  if ( this != &rhs )
  {
    rhs.updateData();
    _data.CopyFrom(rhs._data);
    initialize();
  }
  return *this;
}

const WearerData &Wearer::getData() const
{
  return _data;
}

const google::protobuf::Message& Wearer::getDataPolymorphic() const
{
  return getData();
}

void Wearer::initialize()
{
  _itemSlots.clear();
  for ( auto s = _data.item_slots().begin(); s != _data.item_slots().end(); ++s )
     _itemSlots[ static_cast<ItemSlotType>(*s) ] = nullptr;

  _equippedItems->clear();
  for ( auto a = _data.equipped_items().begin(); a != _data.equipped_items().end(); ++a )
     _equippedItems->push_back( Actor::create(*a) );

  assignItemsToSlots();
}

void Wearer::updateData() const
{
  _data.mutable_equipped_items()->Clear();
  for ( auto a : *_equippedItems )
    _data.mutable_equipped_items()->Add()->CopyFrom(a->getData());

  _data.mutable_item_slots()->Clear();
  for ( auto kv : _itemSlots )
    _data.mutable_item_slots()->Add( static_cast<int>(kv.first) );
}

void Wearer::assignItemsToSlots()
{
  for ( ActorPtr a : _equippedItems->toVector() )
  {
    PickablePtr pickable = a ? a->getFeature<Pickable>() : nullptr;
    if ( pickable && hasSlot( pickable->getItemSlot() ))
    {
      _itemSlots[ pickable->getItemSlot() ] = a;
    }
  }
}

Wearer::Wearer(const WearerData &data)
{
  _data.CopyFrom(data);
  initialize();
}

bool Wearer::equip(ActorPtr item)
{
  bool r = false;

  if ( item != nullptr && item->hasFeature<Pickable>())
  {
    ItemSlotType slot = item->getFeature<Pickable>()->getItemSlot();
    if ( _itemSlots.count(slot) && !isEquipped(slot) )
    {    
      _equippedItems->push_back(item);
      _itemSlots[slot] = item;
      r = true;
    }
  }

  return r;
}

ActorPtr Wearer::unequip(ItemSlotType slot)
{
  ActorPtr r = equipped(slot);

  if (r)
  {
    _equippedItems->remove(r);
    _itemSlots[slot] = nullptr;
  }

  return r;
}

ActorPtr Wearer::unequip(ActorPtr actor)
{
  for (const auto& p : _itemSlots)
  {
    if ( p.second == actor )
    {
      return unequip(p.first);
    }
  }
  return actor;
}

bool Wearer::isEquipped(ItemSlotType slot) const
{
  return (equipped(slot) != nullptr);
}

ActorPtr Wearer::equipped(ItemSlotType slot) const
{
  ActorPtr r;
  auto it = _itemSlots.find(slot);
  if (it != _itemSlots.end())
  {
    r = it->second;
  }

  return r;
}

bool Wearer::hasSlot(ItemSlotType slot) const
{
  return (_itemSlots.find(slot) != _itemSlots.end());
}

std::string Wearer::debug(const std::string &linebreak)
{
  std::string d = " " + linebreak + "-----WEARER-----"+linebreak;
  for(auto slot : _itemSlots)
  {
    ActorPtr eq = equipped(slot.first);
    PickablePtr p = eq ? eq->getFeature<Pickable>() : nullptr;
    d += ItemSlotType2Str(slot.first);
    d +=  ": "
        + (eq ? eq->getName() : "<none>")
        + (p ? " [" + toStr(p->getAmount()) + "]" : "" ) + linebreak;
  }
  d.append("----------------"+linebreak);
  return d;
}

}

