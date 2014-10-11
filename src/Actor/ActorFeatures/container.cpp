#include "container.h"
#include <algorithm>
#include <iostream>
#include "Actor/actor.h"
#include <Utils/ItemPickerGui.h>

Container::Container(size_t maxSize)
  : _maxSize(maxSize)
{
}

bool Container::add(Actor *actor)
{
  bool spaceAvail = size() < _maxSize;

  if (spaceAvail)
    _inventory.push_back(actor);

  return spaceAvail;
}

bool Container::remove(Actor *actor)
{
  auto aIter = std::find(_inventory.begin(), _inventory.end(), actor);
  bool found = (aIter != _inventory.end());

  if (found)
  {
    _inventory.erase(aIter);
  }

  return found;
}

const std::vector<Actor *> &Container::content() const
{
  return _inventory;
}

size_t Container::size() const
{
  return _inventory.size();
}
size_t Container::maxSize() const
{
  return _maxSize;
}

void Container::setMaxSize(const size_t &maxSize)
{
  _maxSize = maxSize;
}

