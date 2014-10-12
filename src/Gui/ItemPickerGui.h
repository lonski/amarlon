#ifndef ITEMPICKERGUI_H
#define ITEMPICKERGUI_H

#include <vector>
#include <string>
#include <libtcod.hpp>

class Actor;

class ItemPickerGui
{
public:
  ItemPickerGui();
  void pick(const std::vector<Actor *> items, std::string title = "");
  int captureItemIndex(TCOD_keycode_t takeAllKey = TCODK_ENTER);
};

#endif // ITEMPICKER_H
