#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>
#include <vector>
#include <list>
#include <actor_feature.h>
#include <actor_type.h>
#include <actor.pb.h>

namespace amarlon {

class Actor;
class Inventory;
class ActorContainer;
class Pickable;
struct Description;
typedef std::shared_ptr<Description> DescriptionPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Pickable> PickablePtr;
typedef std::shared_ptr<Inventory> InventoryPtr;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;

class Inventory : public ActorFeature
{
public:
  typedef std::list<ActorPtr>::iterator iterator;

  const static ActorFeature::Type FeatureType;

  static InventoryPtr create(const InventoryData& data);

  Inventory();
  Inventory(const Inventory& rhs);
  virtual ~Inventory();

  bool operator==(const Inventory& rhs) const;
  Inventory& operator=(const Inventory& rhs);
  virtual const InventoryData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType() { return Inventory::FeatureType; }

  bool add(ActorPtr actor, bool notify = false);
  bool remove(ActorPtr actor, bool notify = false);
  void clear();

  int getGoldAmount() const;
  bool modifyGoldAmount(int modifier, bool notify = false);

  size_t size() const;
  bool empty() const;
  size_t slotCount() const;
  void setSlotCount(const size_t &slotCount);

  void performActionOnActors(std::function<void(ActorPtr)> fun);
  void sort(std::function<bool(ActorPtr, ActorPtr)> fun);
  void sort(std::function<bool(PickablePtr, PickablePtr)> fun);

  std::vector<ActorPtr> items(std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;}) const;
  std::vector<ActorPtr> items(std::function<bool(PickablePtr)> filterFun) const;
  std::vector<ActorPtr> items(ActorType type) const;

  virtual std::string debug(const std::string& linebreak = "\n");

private:
  mutable InventoryData _data;
  ActorContainerPtr _items;

  Inventory(const InventoryData& data);
  void initialize();
  void updateData() const;
  void notifyAdd(ActorPtr actor);
  void notifyRemove(ActorPtr actor, int amount);

};

}



#endif // CONTAINER_H
