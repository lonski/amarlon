#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include "libtcod.hpp"
#include <memory>
#include <Gui/Widget/categorized_menu.h>
#include <Gui/Widget/panel.h>

namespace amarlon {

class Actor;

namespace gui {

class Panel;
typedef std::shared_ptr<Panel> PanelPtr;

class InventoryWindow
{
public:
  const int windowHeight;
  const int windowWidth;

  InventoryWindow(const std::vector<Actor*>& items);

  void render(TCODConsole& console);
  void show(TCODConsole& console);

private:
  Panel _bodyPanel;
  Panel _bagPanel;
  CategorizedMenuPtr _bagMenu;
  const std::vector<Actor*> _items;

  void setupBagPanelWidgets();
  void setupBodyPanelWidgets();

};

}}

#endif // INVENTORY_WINDOW_H
