#ifndef ITEMPICKERGUI_H
#define ITEMPICKERGUI_H

#include <vector>
#include <string>
#include <libtcod.hpp>

class Actor;

class ItemPickerGui
{
public:
  ItemPickerGui(int width = 30, int height = 20);

  void render(const std::vector<Actor *> items, std::string title = "");
  int captureItemIndex(TCOD_keycode_t takeAllKey = TCODK_KPENTER);

private:
  const int _conWidth;
  const int _conHeight;
  TCODConsole _console;

  void renderConsoleFrame(std::string title);
  void blitConsole();
  void renderItems(const std::vector<Actor *> &items);

};

#endif // ITEMPICKER_H
