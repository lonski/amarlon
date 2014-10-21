#include "ItemPicker.h"
#include <algorithm>
#include "World/Map.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include "Gui/Gui.h"
#include "Gui/AmountWindow.h"
#include "Utils/Messenger.h"

ItemPicker::ItemPicker(const std::vector<Actor *> &items, Actor *executor)
  : _items(items)
  , _executor(executor)
  , _singlePick(false)
{
}

std::vector<Actor*> ItemPicker::pick(bool forceGui, bool singlePick)
{
  _singlePick = singlePick;

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
  int index = _pickerGui.pick(_items);

  if (index == -1 && !_singlePick) //take all
  {
    std::for_each(_items.begin(), _items.end(), [&](Actor* a)
    {
      pickSingleItem(a, true);
    });
  }
  else if (index < (int)_items.size() && index >= 0) //take one
  {
    pickSingleItem(_items[index]);
  }
}

void ItemPicker::pickSingleItem(Actor* target, bool takAll)
{
  bool stackable = target->afPickable()->isStackable();
  int amount = target->afPickable()->getAmount();

  //handle stackable
  if ( stackable && amount > 1 && !takAll)
  {
    int tmpAmount = 1;
    if ( !_singlePick )
    {
      AmountWindow aw(amount);
      tmpAmount = aw.getAmount();
    }

    if (tmpAmount < amount)
    {
      amount = tmpAmount;
      target = target->afPickable()->spilt(amount);
    }
  }

  if ( _executor ) //is null when dropping item from player's inventory
  {
    _executor->afContainer()->add(target);
    Messenger::message()->actorPicked(_executor, target, amount);
  }

  _itemsPicked.push_back(target);
}
