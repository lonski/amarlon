#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>
#include <vector>
#include <list>
#include <actor_feature.h>

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

  const static ActorFeature::Type featureType;

  Inventory(DescriptionPtr dsc = nullptr);
  virtual ~Inventory();
  static InventoryPtr create(DescriptionPtr dsc);
  virtual void upgrade(DescriptionPtr dsc);
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

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
  std::vector<ActorPtr> items(int type) const;

  virtual void tickDay();

  virtual std::string debug(const std::string& linebreak = "\n");

private:
  ActorContainerPtr _items;
  size_t _slotCount;
  bool _pushToFront;

  void notifyAdd(ActorPtr actor);
  void notifyRemove(ActorPtr actor, int amount);

};

}



#endif // CONTAINER_H
