#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>
#include <vector>
#include <list>
#include <actor_feature.h>
#include <actor_type.h>

namespace amarlon {

class Actor;
class Inventory;
class ActorContainer;
struct Description;
typedef std::shared_ptr<Description> DescriptionPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Inventory> InventoryPtr;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;

class Inventory : public ActorFeature
{
public:
  typedef std::list<ActorPtr>::iterator iterator;

  const static ActorFeature::Type featureType;

  Inventory(size_t slotCount);
  virtual ~Inventory();
  static InventoryPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  bool add(ActorPtr actor);
  bool remove(ActorPtr actor);
  void clear();

  int getGoldAmount() const;
  bool modifyGoldAmount(int modifier);

  size_t size() const;
  bool empty() const;
  size_t slotCount() const;
  void setSlotCount(const size_t &slotCount);

  void performActionOnActors(std::function<void(ActorPtr)> fun);
  void sort(std::function<bool(ActorPtr, ActorPtr)> fun);

  std::vector<ActorPtr> items(std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;}) const;
  std::vector<ActorPtr> items(ActorType type) const;

private:
  ActorContainerPtr _items;
  size_t _slotCount;
  bool _pushToFront;


};

}



#endif // CONTAINER_H
