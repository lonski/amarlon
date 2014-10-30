#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/panel.h>

namespace amarlon {

class Actor;
class Engine;

namespace gui {

class Panel;
typedef std::shared_ptr<Panel> PanelPtr;

class InventoryWindow
{  
private:
  enum WindowPanel
  {
    BODYSLOTS,
    INVENTORY
  };

public:
  const int windowHeight;
  const int windowWidth;

  InventoryWindow(Engine* engine);

  void render();
  void show();

private:
  std::map<WindowPanel, MenuPtr> _panels;
  WindowPanel _activePanel;

  std::map<int, Actor*> _bagItems;

  Engine* _engine;

  void setupBagPanelWidgets();
  void setupBodyPanelWidgets();
  void fillBag();
  void fillBodySlots();

  void handleKey(TCOD_key_t key);
  void activateNextPanel();
  MenuItemPtr getSelectedItem();

};

}}

#endif // INVENTORY_WINDOW_H
