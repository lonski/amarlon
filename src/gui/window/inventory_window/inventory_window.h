#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include <gui/window/inventory_window/bag_manager.h>
#include <gui/window/inventory_window/body_manager.h>
#include <inventory_panel.h>
#include <awindow.h>

namespace amarlon {

class Actor;
class Engine;

namespace gui {

class InventoryWindow : public AWindow
{
  friend class WindowManager;
  InventoryWindow();

public:
  const int windowHeight;
  const int windowWidth;

  static WindowId getId() { return AWindow::INVENTORY; }

  virtual AWindow& show();
  virtual AWindow& setDefaults();
  virtual void render(TCODConsole& console);

private:
  enum WindowPanel
  {
    BODYSLOTS,
    INVENTORY
  };

  std::map<WindowPanel, AInventoryPanelPtr> _panels;
  WindowPanel _activePanel;

  BagManagerPtr _bagMgr;
  BodyManagerPtr _bodyMgr;

  void initalize();
  void handleKey(TCOD_key_t key);

  void activateNextPanel();
  void activatePreviousPanel();

};

}}

#endif // INVENTORY_WINDOW_H
