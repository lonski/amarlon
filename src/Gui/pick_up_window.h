#ifndef PICK_UP_WINDOW_H
#define PICK_UP_WINDOW_H

#include <vector>
#include <functional>
#include <libtcod.hpp>

namespace amarlon {

class Actor;
class Container;

namespace gui {

class PickUpWindow
{
public:
  /**
   * @brief A window that allow pick uping items using gui
   * @param picker - actor who picks (player)
   * @param container - a container from which the items will be pulled
   * @param filterFunc - a function that filter the content of container
   */
  PickUpWindow(Actor& picker,
               Container& container,
               std::function<bool(Actor*)> filterFunc);

  void show();

private:
  Actor& _picker;
  Container& _container;
  std::function<bool(Actor*)> _filterFunc;

};

}}

#endif // PICK_UP_WINDOW_H
