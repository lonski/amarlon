#ifndef PICK_UP_WINDOW_H
#define PICK_UP_WINDOW_H

#include <vector>
#include <functional>
#include <libtcod.hpp>
#include <gui/widget/menu/items_menu.h>
#include <gui/window/window.h>
#include <utils/console_freezer.h>

namespace amarlon {

class Actor;
class Container;

namespace gui {

class PickUpWindow : public Window
{
private:
  friend class WindowManager;
  PickUpWindow();

public:
  virtual Window& show();
  virtual Window& setDefaults();
  static  WindowId getId() { return Window::PICKUP; }

  /**
   * @param picker - actor who picks (player)
   */
  PickUpWindow& setPicker(Actor* picker);

  /**
   * @param container - a container from which the items will be pulled
   */
  PickUpWindow& setContainer(Container* container);

  /**
   * @param filterFunc - a function that filter the content of container
   */
  PickUpWindow& setFilterFunction(std::function<bool(Actor*)> fun);

private:
  Actor* _picker;
  Container* _container;
  std::function<bool(Actor*)> _filterFunc;

  ConsoleFreezer _freezer;
  gui::ItemsMenu _menu;

};

}}

#endif // PICK_UP_WINDOW_H
