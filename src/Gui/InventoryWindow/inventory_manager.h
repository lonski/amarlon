#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <memory>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/menu/items_menu.h>

namespace amarlon {
  class Actor;
  class Engine;
namespace gui {

class InventoryManager
{
public:
  InventoryManager(ItemsMenuPtr invMenu, MenuPtr bodyMenu, Engine *engine);

  void manage();
  void fillBag();

private:
  enum ItemOperation
  {
    DROP,
    EQUIP
  };

  std::map<int, Actor*> _bagItems;
  ItemsMenuPtr _invMenu;
  MenuPtr _bodyMenu;

  Engine* _engine;

  void render();

  void drop(Actor* item);
  bool handleStackableDrop(Actor*& item);

  void equip(Actor* item);
  bool canEquip(Actor *item);
  void doTheEquip(Actor* item);

  ItemOperation chooseItemOperationFromMenu(Actor* selected);

};

typedef std::shared_ptr<InventoryManager> InventoryManagerPtr;

}}

#endif // INVENTORY_MANAGER_H
