#ifndef WEARER_H
#define WEARER_H

#include <map>
#include "actor_feature.h"
#include "data_gateways/actor_descriptions.h"
#include "container.h"
#include "item_slot_type.h"

namespace amarlon {

class Wearer;
typedef std::shared_ptr<Wearer> WearerPtr;

class Wearer : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Wearer();
  virtual ~Wearer() {}
  static WearerPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  bool equip(ActorPtr item);
  ActorPtr unequip(ItemSlotType slot);
  bool isEquipped(ItemSlotType slot);
  ActorPtr equipped(ItemSlotType slot);
  bool hasSlot(ItemSlotType slot);

private:
  std::map<ItemSlotType, ActorPtr> _itemSlots;
  ContainerPtr _equippedItems;

  static void assignItemsToSlots(WearerPtr wearer);

};


}

#endif // WEARER_H
