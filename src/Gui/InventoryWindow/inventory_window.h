#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/panel.h>
#include <Gui/InventoryWindow/inventory_manager.h>

namespace amarlon {

class Actor;
class Engine;

namespace gui {

class Panel;
typedef std::shared_ptr<Panel> PanelPtr;

class InventoryWindow
{  
public:
  const int windowHeight;
  const int windowWidth;

  InventoryWindow(Engine* engine);

  void render();
  void show();

private:
  enum WindowPanel
  {
    BODYSLOTS,
    INVENTORY
  };

  std::map<WindowPanel, MenuPtr> _panels;
  WindowPanel _activePanel;

  Engine* _engine;

  InventoryManagerPtr _invMgr;

  void fillBodySlots();

  void handleKey(TCOD_key_t key);
  void activateNextPanel();
  void activatePreviousPanel();
  MenuItemPtr getSelectedItem();

  void manageBodySlots();
};

}}

#endif // INVENTORY_WINDOW_H
