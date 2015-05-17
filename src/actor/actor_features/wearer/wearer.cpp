#include "wearer.h"
#include <algorithm>
#include <iostream>
#include "actor/actor.h"
#include "amarlon_except.h"

namespace amarlon {

const ActorFeature::Type Wearer::featureType = ActorFeature::WEARER;

Wearer::Wearer()
  : _equippedItems( new Container(0) )
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
    wearerDsc->eqItems->maxSize = wearerDsc->itemSlots.size();

    std::for_each(wearerDsc->itemSlots.begin(), wearerDsc->itemSlots.end(), [&](ItemSlotType slot)
    {
      w->_itemSlots[slot] = nullptr;
    });

    w->_equippedItems = Container::create(wearerDsc->eqItems);
    if ( w->_equippedItems )
    {
      assignItemsToSlots( w );
    }

  }else throw creation_error("Wrong wearer description!");

  return w;
}

void Wearer::assignItemsToSlots(WearerPtr wearer)
{
  std::vector<ActorPtr> toEquip = wearer->_equippedItems->content();
  std::for_each(toEquip.begin(), toEquip.end(), [&](ActorPtr a)
  {
    if ( a && a->hasFeature<Pickable>())
    {
      wearer->_itemSlots[ a->getFeature<Pickable>()->getItemSlot() ] = a;
    }
    else throw inventory_error("Unequippable item in wearer container!");
  });
}

ActorFeaturePtr Wearer::clone()
{
  WearerPtr cloned( new Wearer );

  for(auto i : _itemSlots)
  {
    cloned->_itemSlots[ i.first ] = nullptr;
  }

  cloned->_equippedItems = std::dynamic_pointer_cast<Container>(_equippedItems->clone());
  assignItemsToSlots(cloned);

  return cloned;
}

bool Wearer::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  WearerPtr crhs = std::dynamic_pointer_cast<Wearer>(rhs);

  if ( crhs != nullptr )
  {
    equal = true;
    //compare item slots and equipped items
    for (int i = (int)ItemSlotType::Null; i != (int)ItemSlotType::End; ++i)
    {
      ItemSlotType slot = (ItemSlotType)i;
      equal &= (hasSlot(slot) == crhs->hasSlot(slot));
      equal &= (isEquipped(slot) == crhs->isEquipped(slot));
      if ( equipped(slot) ) equal &=  ( equipped(slot)->isEqual( crhs->equipped(slot) ));
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
      r = _equippedItems->add(item);
      if ( r ) _itemSlots[slot] = item;
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

bool Wearer::isEquipped(ItemSlotType slot)
{
  return (equipped(slot) != nullptr);
}

ActorPtr Wearer::equipped(ItemSlotType slot)
{
  ActorPtr r;
  auto it = _itemSlots.find(slot);
  if (it != _itemSlots.end())
  {
    r = it->second;
  }

  return r;
}

bool Wearer::hasSlot(ItemSlotType slot)
{
  return (_itemSlots.find(slot) != _itemSlots.end());
}

}
