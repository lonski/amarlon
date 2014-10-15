#ifndef ITEMPICKER_H
#define ITEMPICKER_H

#include <Gui/ItemPickerGui.h>

class Map;

class ItemPicker
{
public:
  ItemPicker(const std::vector<Actor *> &items, Actor* executor = nullptr);
  std::vector<Actor *> pick(bool forceGui = false);

  void pickSingleItem(Actor* target);
  void pickItemsByGui();
private:
  const std::vector<Actor*>& _items;
  std::vector<Actor*> _itemsPicked;
  Actor* _executor;
  ItemPickerGui _pickerGui;

};

#endif // ITEMPICKER_H
