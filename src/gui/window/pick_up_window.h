#ifndef PICK_UP_WINDOW_H
#define PICK_UP_WINDOW_H

#include <vector>
#include <functional>
#include <libtcod.hpp>
#include <gui/widget/menu/items_menu.h>
#include <gui/window/window.h>

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

  /**
   * @brief given function will be called each time item has been successfully picked
   *        it can be for example a message in log
   */
  PickUpWindow& setAfterPickupAction(std::function<void(const std::string& itemName, int pickedAmount)> fun);

  /**
   * @brief given function will be called if item cannot be picked up because
   *        inventory is full. It could be for example error message.
   */
  PickUpWindow& setInventoryFullAction(std::function<void(const std::string& itemName)> fun);

  PickUpWindow& setWindowTitle(const std::string& title);

private:
  Actor* _picker;
  Container* _container;
  std::function<bool(Actor*)> _filterFunc;

  //actions
  std::function<void(const std::string& itemName, int pickedAmount)> _afterPickUpAction;
  std::function<void(const std::string& itemName)> _inventoryFullAction;

  gui::ItemsMenu _menu;

};

}}

#endif // PICK_UP_WINDOW_H
