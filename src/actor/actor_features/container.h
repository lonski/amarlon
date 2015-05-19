#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include "actor_feature.h"
#include "data_gateways/actor_descriptions.h"

namespace amarlon {

class Actor;
class Container;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Container> ContainerPtr;

class Container : public ActorFeature
{
public:
  typedef std::list<ActorPtr>::iterator iterator;

  const static ActorFeature::Type featureType;

  Container(size_t slotCount);
  virtual ~Container();
  static ContainerPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  bool add(ActorPtr actor);
  bool addFront(ActorPtr actor);
  bool remove(ActorPtr actor);
  std::vector<ActorPtr> content(std::function<bool(ActorPtr)>* filterFun = nullptr);
  size_t size() const;
  void performActionOnActors(std::function<void(ActorPtr)> fun);
  void sort(std::function<bool(ActorPtr, ActorPtr)> pred);

  size_t slotCount() const;
  void setSlotCount(const size_t &slotCount);

private:
  std::list<ActorPtr> _inventory;
  size_t _slotCount;
  bool _pushToFront;

  bool pushNewItem(ActorPtr actor);

};

}



#endif // CONTAINER_H
