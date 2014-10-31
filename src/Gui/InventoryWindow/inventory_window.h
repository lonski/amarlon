#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/panel.h>
#include <Gui/InventoryWindow/bag_manager.h>
#include <Gui/InventoryWindow/body_manager.h>

namespace amarlon {

class Actor;
class Engine;

namespace gui {

class InventoryWindow
{  
public:
  const int windowHeight;
  const int windowWidth;

  InventoryWindow(Engine* engine);

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
