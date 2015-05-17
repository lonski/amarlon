#ifndef PICK_UP_WINDOW_H
#define PICK_UP_WINDOW_H

#include <vector>
#include <functional>
#include <libtcod.hpp>
#include <amenu.h>
#include <awindow.h>

namespace amarlon {

class Actor;
class Container;
typedef std::shared_ptr<Container> ContainerPtr;

namespace gui {

class PickUpWindow : public AWindow
{
private:
  friend class WindowManager;
  PickUpWindow();

public:
  virtual AWindow& show();
  virtual AWindow& setDefaults();
  static  WindowId getId() { return AWindow::PICKUP; }

  /**
   * @param picker - actor who picks (player)
   */
  PickUpWindow& setPicker(ActorPtr picker);

  /**
   * @param container - a container from which the items will be pulled
   */
  PickUpWindow& setContainer(ContainerPtr container);

  /**
   * @param filterFunc - a function that filter the content of container
   */
  PickUpWindow& setFilterFunction(std::function<bool(ActorPtr)> fun);

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
  ActorPtr _picker;
  ContainerPtr _container;
  std::function<bool(ActorPtr)> _filterFunc;

  //actions
  std::function<void(const std::string& itemName, int pickedAmount)> _afterPickUpAction;
  std::function<void(const std::string& itemName)> _inventoryFullAction;

  gui::AMenuPtr _menu;

  void fillMenuWithItems();
  void choose();
  ActorPtr getSelectedActor();
  void init();

};

}}

#endif // PICK_UP_WINDOW_H
