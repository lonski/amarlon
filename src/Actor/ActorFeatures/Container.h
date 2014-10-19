#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>
#include "ActorFeature.h"

class Actor;

class Container : public ActorFeature
{
public:
  Container(size_t slotCount);

  bool add(Actor* actor);
  bool remove(Actor* actor);
  const std::vector<Actor*>& content() const;
  size_t size() const;

  size_t slotCount() const;
  void setSlotCount(const size_t &slotCount);

  bool pushNewItem(Actor *actor);
private:
  std::vector<Actor*> _inventory;
  size_t _slotCount;

};

#endif // CONTAINER_H
