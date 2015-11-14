#ifndef WEARER_H
#define WEARER_H

#include <map>
#include <actor_feature.h>
#include <item_slot_type.h>

namespace amarlon {

class Wearer;
class ActorContainer;
typedef std::shared_ptr<Wearer> WearerPtr;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;

class Wearer : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Wearer();
  virtual ~Wearer() {}
  static WearerPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  bool equip(ActorPtr item);
  ActorPtr unequip(ItemSlotType slot);
  ActorPtr unequip(ActorPtr actor);
  bool isEquipped(ItemSlotType slot) const;
  ActorPtr equipped(ItemSlotType slot) const;
  bool hasSlot(ItemSlotType slot) const;

private:
  std::map<ItemSlotType, ActorPtr> _itemSlots;
  ActorContainerPtr _equippedItems;

  static void assignItemsToSlots(WearerPtr wearer);

};


}

#endif // WEARER_H
