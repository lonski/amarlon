#include "wearer.h"
#include <algorithm>
#include <actor_container.h>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_descriptions.h>

namespace amarlon {

const ActorFeature::Type Wearer::featureType = ActorFeature::WEARER;

Wearer::Wearer()
  : _equippedItems( new ActorContainer )
{
}

WearerPtr Wearer::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */  
  WearerPtr w = nullptr;
  WearerDescriptionPtr wearerDsc = std::dynamic_pointer_cast<WearerDescription>(dsc);

  if ( wearerDsc != nullptr )
  {
    w.reset( new Wearer );

    std::for_each(wearerDsc->itemSlots.begin(), wearerDsc->itemSlots.end(), [&](ItemSlotType slot)
    {
      w->_itemSlots[slot] = nullptr;
    });

    for ( auto aDsc : wearerDsc->eqItems )
    {
      w->_equippedItems->push_back( Actor::create(aDsc) );
    }

    if ( w->_equippedItems )
    {
      assignItemsToSlots( w );
    }

  };

  return w;
}

void Wearer::assignItemsToSlots(WearerPtr wearer)
{
  std::vector<ActorPtr> toEquip = wearer->_equippedItems->toVector();
  std::for_each(toEquip.begin(), toEquip.end(), [&](ActorPtr a)
  {
    if ( a && a->hasFeature<Pickable>())
    {
      wearer->_itemSlots[ a->getFeature<Pickable>()->getItemSlot() ] = a;
    }
  });
}

ActorFeaturePtr Wearer::clone()
{
  WearerPtr cloned( new Wearer );

  for(auto i : _itemSlots)
  {
    cloned->_itemSlots[ i.first ] = nullptr;
  }

  cloned->_equippedItems = _equippedItems->clone();
  assignItemsToSlots(cloned);

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
    if (!_equippedItems->remove(r))
    {
      throw std::logic_error("Item equipped in slot, but not present in container!");
    }
    _itemSlots[slot] = nullptr;
  }

  return r;
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

}

