#include "wearer.h"
#include <algorithm>
#include <actor_container.h>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_descriptions.h>

namespace amarlon {

const ActorFeature::Type Wearer::featureType = ActorFeature::WEARER;

Wearer::Wearer(DescriptionPtr dsc)
  : _equippedItems( new ActorContainer )
{
  upgrade(dsc);
  if ( _equippedItems ) assignItemsToSlots();
}

WearerPtr Wearer::create(DescriptionPtr dsc)
{
  return WearerPtr(new Wearer(dsc));
}

void Wearer::upgrade(DescriptionPtr dsc)
{
  WearerDescriptionPtr wearerDsc = std::dynamic_pointer_cast<WearerDescription>(dsc);
  if ( wearerDsc != nullptr )
  {
    for ( auto slot : wearerDsc->itemSlots )
    {
      _itemSlots.insert( std::make_pair(slot, nullptr) );
    }

    for ( auto aDsc : wearerDsc->eqItems )
    {
      _equippedItems->push_back( Actor::create(aDsc) );
    }
  };
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

ActorFeaturePtr Wearer::clone()
{
  WearerPtr cloned( new Wearer );

  for(auto i : _itemSlots)
  {
    cloned->_itemSlots[ i.first ] = nullptr;
  }

  cloned->_equippedItems = _equippedItems->clone();
  cloned->assignItemsToSlots();

  return cloned;
}

bool Wearer::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  WearerPtr crhs = std::dynamic_pointer_cast<Wearer>(rhs);

  if ( crhs != nullptr )
  {
    equal = true;
    //compare item slots and equipped items
    for (auto slot : ItemSlotType())
    {
      equal &= (hasSlot(slot) == crhs->hasSlot(slot));
      equal &= (isEquipped(slot) == crhs->isEquipped(slot));
      if ( equipped(slot) && crhs->equipped(slot) ) equal &=  ( *(equipped(slot)) == *(crhs->equipped(slot)) );
    }
  }

  return equal;
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

