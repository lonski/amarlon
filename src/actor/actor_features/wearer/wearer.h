#ifndef WEARER_H
#define WEARER_H

#include <map>
#include "actor_feature.h"
#include "data_gateways/actor_descriptions.h"
#include "container.h"
#include "item_slot_type.h"

namespace amarlon {

class Wearer : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Wearer();
  virtual ~Wearer() {}
  static Wearer* create(Description* dsc);

  virtual ActorFeature::Type getType() { return featureType; }

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
