#include "Container.h"
#include <algorithm>
#include <iostream>
#include "Actor/Actor.h"
#include <Gui/ItemPickerWindow.h>

Container::Container(size_t maxSize)
  : _slotCount(maxSize)
{
}

bool Container::add(Actor *actor)
{
  bool added = false;

  //handle stackable
  if ( actor->afPickable()->isStackable() )
  {
    auto invIter = find_if(_inventory.begin(), _inventory.end(), [&](Actor* iItem)
                   {
                     return iItem->getId() == actor->getId();
                   });

    if (invIter != _inventory.end()) //merge
    {
      Actor* actorToStackWith = *invIter;

      int invAmount = actorToStackWith->afPickable()->getAmount();
      int amountToStack = actor->afPickable()->getAmount();

      actorToStackWith->afPickable()->setAmount( invAmount + amountToStack );

      delete actor;
      actor = nullptr;
      added = true;
    }
    else
    {
      added = pushNewItem(actor);
    }

  }
  //handle non stackable
  else
  {
    added = pushNewItem(actor);
  }

  return added;
}

bool Container::pushNewItem(Actor *actor)
{
  bool slotsAvail = size() < _slotCount;

  if (slotsAvail)
    _inventory.push_back(actor);

  return slotsAvail;
}

bool Container::remove(Actor *actor)
{
  auto aIter = std::find(_inventory.begin(), _inventory.end(),actor);
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
size_t Container::slotCount() const
{
  return _slotCount;
}

void Container::setSlotCount(const size_t &maxSize)
{
  _slotCount = maxSize;
}

