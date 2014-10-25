#ifndef ITEMPICKERGUI_H
#define ITEMPICKERGUI_H

#include <vector>
#include <string>
#include <libtcod.hpp>

namespace amarlon {

class Actor;

namespace gui {

class ItemPickerWindow
{
public:
  ItemPickerWindow(std::string title = "", int width = 30, int height = 20);

  /**
   * @return index of choosen item in array
   *         Special cases:
   *         -2 -> no item selected
   *         -1 -> all items selected
   */
  int pick(const std::vector<Actor *> &items);
  void setTitle(const std::string &title);

private:
  std::string _title;

  const int _conWidth;
  const int _conHeight;
  TCODConsole _console;

  const std::vector<Actor *>* _items;
  int _index;

  void render();
  void renderConsoleFrame(std::string title);
  void blitConsole();
  void renderItems();
  void handlePressedKey(TCOD_key_t key);

};

}}
#endif // ITEMPICKER_H
