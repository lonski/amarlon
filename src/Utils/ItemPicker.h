#ifndef ITEMPICKER_H
#define ITEMPICKER_H

#include <Gui/ItemPickerGui.h>

class Map;

class ItemPicker
{
public:
  ItemPicker(Actor* executor, const std::vector<Actor *> &items);
  std::vector<Actor *> pick(bool forceGui = false);

  void pickSingleItem(Actor* target);
  void pickItemsByGui();
private:
  const std::vector<Actor*>& _items;
  std::vector<Actor*> _itemsPicked;
  Actor* _executor;

};

#endif // ITEMPICKER_H
