#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <memory>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/menu/items_menu.h>

namespace amarlon {
  class Actor;
  class Engine;
namespace gui {

class BagManager
{
public:
  BagManager(ItemsMenuPtr bagMenu, MenuPtr bodyMenu);

  void manage();
  void fillBag();

private:
  enum ItemOperation
  {
    DROP,
    EQUIP
  };

  std::map<int, Actor*> _bagItems;
  ItemsMenuPtr _bagMenu;
  MenuPtr _bodyMenu;

  void render();

  void drop(Actor* item);
  bool handleStackableDrop(Actor*& item);

  void equip(Actor* item);
  bool canEquip(ItemSlotType slot);
  void doTheEquip(Actor* item);

  ItemOperation chooseItemOperationFromMenu(Actor* selected);

};

typedef std::shared_ptr<BagManager> BagManagerPtr;

}}

#endif // INVENTORY_MANAGER_H
