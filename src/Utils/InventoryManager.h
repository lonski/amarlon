#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Gui/ItemPickerGui.h"
#include <string>

class Actor;

class InventoryManager
{
public:
  InventoryManager(Actor* actor);

  void display();
  void setTitle(const std::string& title);
  std::vector<Actor*> pickItems();

private:
  ItemPickerGui _pickerGui;
  Actor* _actor;
  std::string _title;

};

#endif // INVENTORYMANAGER_H
