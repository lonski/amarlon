#include "ItemPicker.h"
#include <algorithm>
#include "World/Map.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include "Gui/Gui.h"
#include "Gui/AmountWindow.h"

ItemPicker::ItemPicker(const std::vector<Actor *> &items, Actor *executor)
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
  int index = _pickerGui.pick(_items);

  if (index == -1) //take all
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
    AmountWindow aw(amount);
    int tmpAmount = aw.getAmount();

    if (tmpAmount < amount)
    {
      amount = tmpAmount;
      target = target->afPickable()->spilt(amount);
    }
  }

  if ( _executor ) //is null when dropping item from player's inventory
  {
    std::string eName = _executor->getName() == "Player" ? "You" : _executor->getName();
    std::string iName = tolowers(target->getName());

    _executor->afContainer()->add(target);

    if (amount > 1)
      Gui::Root.message(eName + " picked " + iName + " (" + std::to_string(amount) + ").", TCODColor::darkYellow );
    else
      Gui::Root.message(eName + " picked " + iName + ".", TCODColor::darkYellow );
  }

  _itemsPicked.push_back(target);
}
