#ifndef WEARER_H
#define WEARER_H

#include <map>
#include <actor_feature.h>
#include <item_slot_type.h>
#include <actor.pb.h>

namespace amarlon {

class Wearer;
class ActorContainer;
typedef std::shared_ptr<Wearer> WearerPtr;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;

class Wearer : public ActorFeature
{
public:
  const static ActorFeature::Type FeatureType;

  static WearerPtr create(const WearerData& data);

  Wearer();
  Wearer(const Wearer& rhs);
  virtual ~Wearer();

  bool operator==(const Wearer& rhs) const;
  Wearer& operator=(const Wearer& rhs);
  virtual const WearerData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType() { return FeatureType; }

  bool equip(ActorPtr item);
  ActorPtr unequip(ItemSlotType slot);
  ActorPtr unequip(ActorPtr actor);
  bool isEquipped(ItemSlotType slot) const;
  ActorPtr equipped(ItemSlotType slot) const;
  bool hasSlot(ItemSlotType slot) const;

  virtual std::string debug(const std::string& linebreak = "\n");

private:
  mutable WearerData _data;
  std::map<ItemSlotType, ActorPtr> _itemSlots;
  ActorContainerPtr _equippedItems;

  Wearer(const WearerData& data);
  void assignItemsToSlots();
  void initialize();
  void updateData() const;

};


}

#endif // WEARER_H
