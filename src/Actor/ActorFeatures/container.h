#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>

class Actor;

class Container
{
public:
  Container(size_t maxSize);
  void setOwner(Actor* owner);

  bool add(Actor* actor);
  bool remove(Actor* actor);
  const std::vector<Actor*>& content() const;
  size_t size() const;

  size_t maxSize() const;
  void setMaxSize(const size_t &maxSize);

private:
  Actor* _owner;
  std::vector<Actor*> _inventory;
  size_t _maxSize;

};

#endif // CONTAINER_H
