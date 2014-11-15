#ifndef WEARER_H
#define WEARER_H

#include <map>
#include "../ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"
#include "../Container.h"
#include "item_slot_type.h"

namespace amarlon {

class Wearer : public ActorFeature
{
public:
  Wearer();
  virtual ~Wearer() {}
  static Wearer* create(Description* dsc);

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature* rhs);

  bool equip(Actor* item);
  Actor* unequip(ItemSlotType slot);
  bool isEquipped(ItemSlotType slot);
  Actor* equipped(ItemSlotType slot);
  bool hasSlot(ItemSlotType slot);

private:
  std::map<ItemSlotType, Actor*> _itemSlots;
  ContainerPtr _equippedItems;

  static void assignItemsToSlots(Wearer* wearer);

};

}

#endif // WEARER_H
