#include "ItemPicker.h"
#include <algorithm>
#include "World/map.h"
#include "Actor/actor.h"

ItemPicker::ItemPicker(Actor *executor, const std::vector<Actor *> &items)
  : _items(items)
  , _executor(executor)
{
}

std::vector<Actor*> ItemPicker::pick(bool forceGui)
{
  if (_items.size() > 1 || (forceGui && !_items.empty()))
  {
    pickItemsByGui();
  }
  else if (!_items.empty())
  {
    pickSingleItem(_items[0]);
  }

  return _itemsPicked;
}

void ItemPicker::pickItemsByGui()
{
  ItemPickerGui pickerGui;
  pickerGui.pick(_items);

  int index = pickerGui.captureItemIndex();

  if (index == -1) //take all
  {
    std::for_each(_items.begin(), _items.end(), [&](Actor* a)
    {
      pickSingleItem(a);
    });
  }
  else if (index < (int)_items.size() && index >= 0) //take one
  {
    pickSingleItem(_items[index]);
  }
}

void ItemPicker::pickSingleItem(Actor* target)
{
  if (_executor)
  {
    target->afPickable->pick(target, _executor);
  }

  _itemsPicked.push_back(target);
}
