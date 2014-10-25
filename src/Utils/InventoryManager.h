#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Gui/ItemPickerWindow.h"
#include <string>

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
  ItemPickerGui _pickerGui;
  Actor* _actor;
  std::string _title;

};

}

#endif // INVENTORYMANAGER_H
