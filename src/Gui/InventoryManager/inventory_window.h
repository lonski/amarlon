#ifndef INVENTORY_WINDOW_H
#define INVENTORY_WINDOW_H

#include "libtcod.hpp"
#include <memory>
#include "../Widget/panel.h"

namespace amarlon { namespace gui {

class Panel;
typedef std::shared_ptr<Panel> PanelPtr;

class InventoryWindow
{
public:
  const int windowHeight;
  const int windowWidth;

  InventoryWindow();

  void render(TCODConsole& console);
  void show(TCODConsole& console);

  void setupBagPanelWidgets();
  void setupBodyPanelWidgets();
private:
  Panel _bodyPanel;
  Panel _bagPanel;

};

}}

#endif // INVENTORY_WINDOW_H
