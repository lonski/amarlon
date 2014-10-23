#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>
#include "ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"

class Actor;

class Container : public ActorFeature
{
public:
  Container(size_t slotCount);
  static Container* create(const ContainerDescription& dsc);

  virtual Container* clone();
  bool add(Actor* actor);
  bool remove(Actor* actor);
  std::vector<Actor *> content(bool(*filterFun)(Actor *) = nullptr);
  size_t size() const;

  size_t slotCount() const;
  void setSlotCount(const size_t &slotCount);

  bool pushNewItem(Actor *actor);
private:
  std::vector<Actor*> _inventory;
  size_t _slotCount;

};

#endif // CONTAINER_H
