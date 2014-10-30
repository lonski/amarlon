#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>
#include <vector>
#include <string>
#include "ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"
#include <functional>

namespace amarlon {

class Actor;

class Container : public ActorFeature
{
public:
  Container(size_t slotCount);
  virtual ~Container();
  static Container* create(const ContainerDescription& dsc);

  virtual Container* clone();
  virtual bool isEqual(ActorFeature* rhs);

  bool add(Actor* actor);
  bool remove(Actor* actor);
  std::vector<Actor *> content(std::function<bool(Actor *)>* filterFun = nullptr);
  size_t size() const;

  size_t slotCount() const;
  void setSlotCount(const size_t &slotCount);

  bool pushNewItem(Actor *actor);
private:
  std::vector<Actor*> _inventory;
  size_t _slotCount;

};

typedef std::shared_ptr<Container> ContainerPtr;

}

#endif // CONTAINER_H
