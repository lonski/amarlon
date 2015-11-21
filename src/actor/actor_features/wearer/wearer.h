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

  Wearer(DescriptionPtr dsc = nullptr);
  virtual ~Wearer() {}
  static WearerPtr create(DescriptionPtr dsc);
  virtual void upgrade(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  bool equip(ActorPtr item);
  ActorPtr unequip(ItemSlotType slot);
  ActorPtr unequip(ActorPtr actor);
  bool isEquipped(ItemSlotType slot) const;
  ActorPtr equipped(ItemSlotType slot) const;
  bool hasSlot(ItemSlotType slot) const;

  virtual std::string debug(const std::string& linebreak = "\n");

private:
  std::map<ItemSlotType, ActorPtr> _itemSlots;
  ActorContainerPtr _equippedItems;

  void assignItemsToSlots();

};


}

#endif // WEARER_H
