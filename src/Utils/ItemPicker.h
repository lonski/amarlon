#ifndef ITEMPICKER_H
#define ITEMPICKER_H

#include <Gui/ItemPickerWindow.h>

namespace amarlon {

class Map;

class ItemPicker
{
public:
  ItemPicker(const std::vector<Actor *> &items, Actor* executor = nullptr);
  std::vector<Actor *> pick(bool forceGui = false, bool singlePick = false);

private:
  const std::vector<Actor*>& _items;
  std::vector<Actor*> _itemsPicked;
  Actor* _executor;
  ItemPickerGui _pickerGui;
  bool _singlePick;

  void pickItemsByGui();
  void pickSingleItem(Actor* target, bool takAll = false);

};

}

#endif // ITEMPICKER_H
