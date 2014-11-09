#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/panel.h>
#include <Gui/Window/InventoryWindow/bag_manager.h>
#include <Gui/Window/InventoryWindow/body_manager.h>
#include <Gui/Window/window.h>

namespace amarlon {

class Actor;
class Engine;

namespace gui {

class InventoryWindow : public Window
{
  friend class WindowManager;
  InventoryWindow();

public:
  const int windowHeight;
  const int windowWidth;

  virtual Window& show();
  virtual Window& setDefaults();
  static WindowId getId() { return Window::INVENTORY; }


private:
  enum WindowPanel
  {
    BODYSLOTS,
    INVENTORY
  };

  std::map<WindowPanel, MenuPtr> _panels;
  WindowPanel _activePanel;

  BagManagerPtr _bagMgr;
  BodyManagerPtr _bodyMgr;

  void initalize();
  void render();
  void handleKey(TCOD_key_t key);

  void activateNextPanel();
  void activatePreviousPanel();

};

}}

#endif // INVENTORY_WINDOW_H
