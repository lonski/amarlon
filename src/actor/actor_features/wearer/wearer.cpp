#include "wearer.h"
#include <algorithm>
#include <actor_container.h>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_descriptions.h>
#include <character.h>
#include <race.h>

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
      _itemSlots.insert( std::make_pair((ItemSlotType)slot, std::make_pair(nullptr,false) ) );
    }

    for ( auto aDsc : wearerDsc->eqItems )
    {
      _equippedItems->push_back( Actor::create(aDsc) );
    }
  };
}

DescriptionPtr Wearer::toDescriptionStruct(ActorFeaturePtr)
{
  WearerDescriptionPtr dsc(new WearerDescription);

  for ( auto& kv : _itemSlots )
    dsc->itemSlots.push_back((int)kv.first);

  for (ActorPtr a : *_equippedItems)
    dsc->eqItems.push_back(a->toDescriptionStruct());

  return dsc;
}

void Wearer::assignItemsToSlots()
{
  for ( ActorPtr a : _equippedItems->toVector() )
  {
    PickablePtr pickable = a ? a->getFeature<Pickable>() : nullptr;
    if ( pickable && hasSlot( pickable->getItemSlot() ))
    {
      _itemSlots[ pickable->getItemSlot() ] = std::make_pair(a, false);
    }
  }
}

void Wearer::setBlocked(ItemSlotType slot, bool blocked)
{
  if ( hasSlot(slot) && !isEquipped(slot) )
  {
    auto& p = _itemSlots[slot];
    p.second = blocked;
  }
}

ActorFeaturePtr Wearer::clone()
{
  WearerPtr cloned( new Wearer );

  for(auto i : _itemSlots)
  {
    cloned->_itemSlots[ i.first ] = std::make_pair(nullptr, false);
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

RaceType getRace(ActorPtr actor)
{
  if ( !actor ) return RaceType::NoRace;

  CharacterPtr c = actor->getFeature<Character>();

  return c ? c->getRace()->getType() : RaceType::NoRace;
}

bool Wearer::equip(ActorPtr item)
{
  if ( !item ) return false;

  PickablePtr pickable = item->getFeature<Pickable>();
  if ( !pickable ) return false;

  ItemSlotType slot = pickable->getItemSlot();

  if ( hasSlot(slot) && !isEquipped(slot) )
  {
    _equippedItems->push_back(item);
    _itemSlots[slot] = std::make_pair(item, false);

    return true;
  }

  return false;
}

ActorPtr Wearer::unequip(ItemSlotType slot)
{
  ActorPtr r = equipped(slot);

  if (r)
  {
    _equippedItems->remove(r);
    _itemSlots[slot] = std::make_pair(nullptr, false);
  }

  return r;
}

ActorPtr Wearer::unequip(ActorPtr actor)
{
  for (const auto& p : _itemSlots)
  {
    if ( p.second.first == actor )
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

bool Wearer::isBlocked(ItemSlotType slot) const
{
  auto it = _itemSlots.find(slot);
  return it != _itemSlots.end() ? it->second.second : false;
}

ActorPtr Wearer::equipped(ItemSlotType slot) const
{
  ActorPtr r;
  auto it = _itemSlots.find(slot);
  if (it != _itemSlots.end())
  {
    r = it->second.first;
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
    bool blocked = isBlocked(slot.first);
    PickablePtr p = eq ? eq->getFeature<Pickable>() : nullptr;
    d += ItemSlotType2Str(slot.first);
    d +=  ": "
        + (eq ? eq->getName() : "<none>")
        + (p ? " [" + toStr(p->getAmount()) + "]" : "" )
        + ( blocked ? " [BLOCKED] " : "" ) + linebreak;
  }
  d.append("----------------"+linebreak);
  return d;
}

}

