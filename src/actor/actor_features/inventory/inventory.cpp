#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_descriptions.h>
#include <actor_container.h>


namespace amarlon {

const ActorFeature::Type Inventory::FeatureType = ActorFeature::INVENTORY;

InventoryPtr Inventory::create(const InventoryData &data)
{
  return InventoryPtr( new Inventory(data) );
}

Inventory::Inventory()
  : _items( new ActorContainer )
{
}

Inventory::Inventory(const Inventory& rhs)
{
  *this = rhs;
}

Inventory::Inventory(const InventoryData &data)
{
  _data.CopyFrom(data);
  initialize();
}

void Inventory::initialize()
{
  _items->clear();
  for ( auto aIt = _data.items().begin(); aIt != _data.items().end(); ++aIt)
    _items->push_back(Actor::create(*aIt));
}

void Inventory::updateData() const
{
  _data.mutable_items()->Clear();
  for ( auto a : *_items )
    _data.mutable_items()->Add()->CopyFrom(a->getData());
}

Inventory::~Inventory()
{
}

bool Inventory::operator==(const Inventory &rhs) const
{
  updateData();
  rhs.updateData();
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Inventory &Inventory::operator=(const Inventory &rhs)
{
  if ( this != &rhs )
  {
    rhs.updateData();
    _data.CopyFrom(rhs._data);
    initialize();
  }
  return *this;
}

const InventoryData &Inventory::getData() const
{
  return _data;
}

const google::protobuf::Message& Inventory::getDataPolymorphic() const
{
  return getData();
}

void Inventory::notifyRemove(ActorPtr actor, int amount)
{
  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    std::string item = actor->getName();
    if ( amount > 1 ) item += " (" + toStr(amount) + ")";
    owner->notify( Event( EventId::Item_Removed, {{"item", item}} ) );
  }
}

void Inventory::notifyAdd(ActorPtr actor)
{
  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    std::string item = actor->getName();

    PickablePtr p = actor->getFeature<Pickable>();
    if ( p && p->isStackable() && p->getAmount() > 1 )
      item += " (" + toStr(p->getAmount()) + ")";

    owner->notify( Event( EventId::Item_Added, {{"item", item}} ) );
  }
}

bool Inventory::add(ActorPtr actor, bool notify)
{
  _items->push_back(actor);

  if ( _items->size() > _data.slotcount() ) //this means actor took new slot (not stacked)
  {
    _items->remove( actor );
    return false;
  }

  if ( notify ) notifyAdd(actor);

  return true;
}

bool Inventory::remove(ActorPtr actor, bool notify)
{
  bool r = _items->remove(actor);
  if ( r && notify ) notifyRemove(actor, 1);
  return r;
}

size_t Inventory::size() const
{
  return _items->size();
}

bool Inventory::empty() const
{
  return _items->empty();
}

void Inventory::clear()
{
  _items->clear();
}

bool Inventory::modifyGoldAmount(int modifier, bool notify)
{
  bool r = false;

  auto i = items(ActorType::GoldCoin);
  if ( !i.empty() )
  {
    PickablePtr p = i.front()->getFeature<Pickable>();
    if ( p && p->getAmount() >= modifier )
    {
      if ( modifier < 0 )
      {
        remove( p->spilt( -modifier ) );
        if ( notify ) notifyRemove(i.front(), -modifier);
      }
      else
      {
        p->setAmount( p->getAmount() + modifier );
        if ( notify ) notifyAdd(i.front());
      }

      r = true;
    }
  }

  return r;
}

int Inventory::getGoldAmount() const
{
  int amount = 0;

  auto i = items(ActorType::GoldCoin);
  if ( !i.empty() )
  {
    PickablePtr p = i.front()->getFeature<Pickable>();
    if ( p ) amount = p->getAmount();
  }

  return amount;
}

void Inventory::performActionOnActors(std::function<void(ActorPtr)> fun)
{
  std::for_each(_items->begin(), _items->end(), fun);
}

void Inventory::sort(std::function<bool(ActorPtr, ActorPtr)> fun)
{
  _items->sort(fun);
}

void Inventory::sort(std::function<bool (PickablePtr, PickablePtr)> fun)
{
  sort([&fun](ActorPtr l, ActorPtr r){
    PickablePtr pl = l ? l->getFeature<Pickable>() : nullptr;
    PickablePtr pr = r ? r->getFeature<Pickable>() : nullptr;
    return fun(pl, pr);
  });
}

size_t Inventory::slotCount() const
{
  return _data.slotcount();
}

void Inventory::setSlotCount(const size_t &maxSize)
{
  _data.set_slotcount(maxSize);
}

std::vector<ActorPtr> Inventory::items(std::function<bool(ActorPtr)> filterFun) const
{
  std::vector<ActorPtr> items;

  for (auto i : *_items)
  {
    if ( filterFun(i) )
    {
      items.push_back(i);
    }
  }

  return items;
}

std::vector<ActorPtr> Inventory::items(std::function<bool (PickablePtr)> filterFun) const
{
  return items([&filterFun](ActorPtr a){
    PickablePtr p = a ? a->getFeature<Pickable>() : nullptr;
    return p ? filterFun(p) : false;
  });
}

std::vector<ActorPtr> Inventory::items(ActorType type) const
{
  return items([&type](ActorPtr a){ return a->getType() == type;});
}

std::string Inventory::debug(const std::string &linebreak)
{
  std::string d = " " + linebreak + "-----INVENTORY ["
                      + toStr(_items->size()) + "/"
                      + toStr(_data.slotcount())
                      + "]-----" +linebreak;

  for(auto item : *_items)
  {
    PickablePtr p = item ? item->getFeature<Pickable>() : nullptr;
    d += item->getName() + (p ? " [" + toStr(p->getAmount()) + "]" : "" ) + linebreak;
  }
  d.append("-------------------"+linebreak);
  return d;
}

}

