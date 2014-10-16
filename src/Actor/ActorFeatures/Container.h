#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>
#include "ActorFeature.h"

class Actor;

class Container : public ActorFeature
{
public:
  Container(size_t maxSize);

  bool add(Actor* actor);
  bool remove(Actor* actor);
  const std::vector<Actor*>& content() const;
  size_t size() const;

  size_t maxSize() const;
  void setMaxSize(const size_t &maxSize);

private:
  std::vector<Actor*> _inventory;
  size_t _maxSize;

};

#endif // CONTAINER_H
