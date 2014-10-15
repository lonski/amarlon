#include "InventoryManager.h"
#include "Actor/Actor.h"
#include "ItemPicker.h"
#include <algorithm>

InventoryManager::InventoryManager(Actor* actor)
  : _actor(actor)
{
}

void InventoryManager::display()
{
  if (_actor->afContainer())
  {
    pickerGui.render(_actor->afContainer()->content(),_title);
    pickerGui.captureItemIndex();
  }
}

void InventoryManager::setTitle(const std::string &title)
{
  _title = title;
}

std::vector<Actor *> InventoryManager::pickItems()
{
  std::vector<Actor*> picked;

  if (_actor->afContainer())
  {
    ItemPicker picker(NULL, _actor->afContainer()->content());
    picked = picker.pick(true);

    std::for_each(picked.begin(), picked.end(), [&](Actor* a)
    {
      _actor->afContainer()->remove( a->afPickable()->drop() );
    });
  }

  return picked;
}
