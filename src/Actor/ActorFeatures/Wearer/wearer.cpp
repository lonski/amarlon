#include "wearer.h"
#include "Actor/Actor.h"
#include <algorithm>
#include <iostream>
#include <amarlon_except.h>

namespace amarlon {

Wearer::Wearer()
  : _equippedItems( new Container(0) )
{
}

Wearer* Wearer::create(Description *dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */  
  Wearer* w = nullptr;
  WearerDescription* wearerDsc = dynamic_cast<WearerDescription*>(dsc);

  if ( wearerDsc != nullptr )
  {
    w = new Wearer;
    wearerDsc->eqItems.maxSize = wearerDsc->itemSlots.size();

    std::for_each(wearerDsc->itemSlots.begin(), wearerDsc->itemSlots.end(), [&](ItemSlotType slot)
    {
      w->_itemSlots[slot] = nullptr;
    });

    w->_equippedItems.reset( Container::create(&wearerDsc->eqItems) );
    if ( w->_equippedItems )
    {
      assignItemsToSlots( w );
    }

  }else throw creation_error("Wrong wearer description!");

  return w;
}

void Wearer::assignItemsToSlots(Wearer* wearer)
{
  std::vector<Actor*> toEquip = wearer->_equippedItems->content();
  std::for_each(toEquip.begin(), toEquip.end(), [&](Actor* a)
  {
    if ( a != nullptr && a->afPickable() != nullptr)
    {
      wearer->_itemSlots[ a->afPickable()->getItemSlot() ] = a;
    }
    else throw inventory_error("Unequippable item in wearer container!");
  });
}

ActorFeature* Wearer::clone()
{
  Wearer* cloned = new Wearer;

  for(auto i : _itemSlots)
  {
    cloned->_itemSlots[ i.first ] = nullptr;
  }

  cloned->_equippedItems.reset( _equippedItems->clone() );
  assignItemsToSlots(cloned);

  return cloned;
}

bool Wearer::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  Wearer* crhs = dynamic_cast<Wearer*>(rhs);

  if ( crhs != nullptr )
  {
    equal = true;
    //compare item slots and equipped items
    for (int i = (int)ItemSlotType::Null; i != (int)ItemSlotType::End; ++i)
    {
      ItemSlotType slot = (ItemSlotType)i;
      equal &= (hasSlot(slot) == crhs->hasSlot(slot));
      equal &= (isEquipped(slot) == crhs->isEquipped(slot));
      if ( equipped(slot) != nullptr ) equal &=  ( equipped(slot)->isEqual( crhs->equipped(slot) ));
    }
  }

  return equal;
}

bool Wearer::equip(Actor *item)
{
  bool r = false;

  if ( item != nullptr && item->afPickable())
  {
    ItemSlotType slot = item->afPickable()->getItemSlot();
    if ( _itemSlots.count(slot) && !isEquipped(slot) )
    {    
      r = _equippedItems->add(item);
      if ( r ) _itemSlots[slot] = item;
    }
  }

  return r;
}

Actor* Wearer::unequip(ItemSlotType slot)
{
  Actor* r = equipped(slot);

  if (r != nullptr)
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

Actor* Wearer::equipped(ItemSlotType slot)
{
  Actor* r = nullptr;
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
