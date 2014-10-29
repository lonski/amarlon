#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include <memory>
#include <libtcod.hpp>
#include <Gui/Widget/menu/menu.h>
#include <Gui/Widget/panel.h>

namespace amarlon {

class Actor;

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

  InventoryWindow(Actor* actor);

  void render(TCODConsole& console);
  void show(TCODConsole& console);

private:
  std::map<WindowPanel, MenuPtr> _panels;

  std::map<int, Actor*> _bagItems;

  Actor* _actor;
  WindowPanel _activePanel;

  void setupBagPanelWidgets();
  void setupBodyPanelWidgets();
  void fillBag();

  void handleKey(TCOD_key_t key);
  void activateNextPanel();

};

}}

#endif // INVENTORY_WINDOW_H
