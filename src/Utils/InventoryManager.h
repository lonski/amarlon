#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <string>
#include <Gui/ItemPickerWindow.h>
#include <Gui/InventoryManager/inventory_window.h>

namespace amarlon {

class Actor;

class InventoryManager
{
public:
  InventoryManager(Actor* actor);

  void display();
  void setTitle(const std::string& title);
  std::vector<Actor*> pickItems(bool singlePick = false);
  Actor* chooseItemToUse();

private:
  gui::InventoryWindow _invGui;
  gui::ItemPickerWindow _pickerGui;
  Actor* _actor;
  std::string _title;

};

}

#endif // INVENTORYMANAGER_H
