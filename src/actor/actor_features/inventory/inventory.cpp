#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_descriptions.h>
#include <actor_container.h>

namespace amarlon {

const ActorFeature::Type Inventory::featureType = ActorFeature::INVENTORY;

Inventory::Inventory(size_t maxSize)
  : _items( new ActorContainer )
  , _slotCount(maxSize)
  , _pushToFront(false)
{
}

Inventory::~Inventory()
{
}

InventoryPtr Inventory::create(DescriptionPtr dsc)
{  
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  InventoryPtr cont;
  InventoryDescriptionPtr contDsc = std::dynamic_pointer_cast<InventoryDescription>(dsc);

  if ( contDsc != nullptr )
  {
    cont.reset( new Inventory(contDsc->maxSize) );

    std::for_each(contDsc->content.begin(), contDsc->content.end(), [&](ActorDescriptionPtr aDsc)
    {
      if ( aDsc )
      {
        ActorPtr a = Actor::create(aDsc->id);
        a->deserialize( aDsc );
        cont->add( a );
      }
    });
  }

  return cont;
}

ActorFeaturePtr Inventory::clone()
{
  InventoryPtr cloned( new Inventory( _slotCount ) );
  cloned->_items = _items->clone();

  return cloned;
}

bool Inventory::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  InventoryPtr crhs = std::dynamic_pointer_cast<Inventory>(rhs);
  if (crhs != nullptr)
  {
    equal = (_slotCount == crhs->_slotCount);    
    equal &= std::equal(_items->begin(), _items->end(), crhs->_items->begin(),
                        [](ActorPtr l, ActorPtr r){ return *l == *r; });
  }

  return equal;
}

bool Inventory::add(ActorPtr actor)
{
  _items->push_back(actor);

  if ( _items->size() > _slotCount ) //this means actor took new slot (not stacked)
  {
    _items->remove( actor );
    return false;
  }
  return true;
}

bool Inventory::remove(ActorPtr actor)
{
  return _items->remove(actor);
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

bool Inventory::modifyGoldAmount(int modifier)
{
  bool r = false;

  auto i = items(ActorType::GoldCoin);
  if ( !i.empty() )
  {
    PickablePtr p = i.front()->getFeature<Pickable>();
    if ( p && p->getAmount() >= modifier )
    {
      if ( modifier < 0 )
        remove( p->spilt( -modifier ) );
      else
        p->setAmount( p->getAmount() + modifier );

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

size_t Inventory::slotCount() const
{
  return _slotCount;
}

void Inventory::setSlotCount(const size_t &maxSize)
{
  _slotCount = maxSize;
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

std::vector<ActorPtr> Inventory::items(ActorType type) const
{
  return items([&type](ActorPtr a){ return a->getType() == type;});
}

}

