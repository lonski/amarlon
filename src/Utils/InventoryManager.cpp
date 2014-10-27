#include "InventoryManager.h"
#include "Actor/Actor.h"
#include "ItemPicker.h"
#include <algorithm>

namespace amarlon {

InventoryManager::InventoryManager(Actor* actor)
  : _actor(actor)
{
}

void InventoryManager::display()
{
//  if (_actor->afContainer())
//  {
//    _pickerGui.pick(_actor->afContainer()->content());
//  }
  _invGui.show(*TCODConsole::root);
}

void InventoryManager::setTitle(const std::string &title)
{
  _title = title;
  _pickerGui.setTitle(_title);
}

std::vector<Actor *> InventoryManager::pickItems(bool singlePick)
{
  std::vector<Actor*> picked;

  if (_actor->afContainer())
  {
    std::vector<Actor*> allItems = _actor->afContainer()->content();
    ItemPicker picker(allItems);
    picked = picker.pick(true, singlePick);

    std::for_each(picked.begin(), picked.end(), [&](Actor* a)
    {
      _actor->afContainer()->remove( a );
    });
  }

  return picked;
}

Actor *InventoryManager::chooseItemToUse()
{
  Actor* toUse = nullptr;

  if (_actor->afContainer())
  {        
    std::vector<Actor*> items = _actor->afContainer()->content( [&](Actor* a)
    {
      return a->afPickable() && a->afPickable()->getEffect();
    });
    ItemPicker picker(items);

    items = picker.pick(true, true);
    if (!items.empty()) toUse = items[0];
  }

  return toUse;
}

}
