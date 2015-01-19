#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include "gui/widget/menu/menu.h"
#include "gui/widget/panel.h"
#include "gui/window/inventory_window/bag_manager.h"
#include "gui/window/inventory_window/body_manager.h"
#include "gui/window/window.h"

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
