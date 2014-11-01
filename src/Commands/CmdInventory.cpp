#include "CmdInventory.h"
#include <iostream>
#include <algorithm>
#include <Gui/InventoryWindow/inventory_window.h>

namespace amarlon {

CmdInventory::CmdInventory(Engine *engine)
  : Command(engine)
{
}

bool CmdInventory::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'i' );
}

void CmdInventory::execute(Actor*)
{  
  if ( !_invWindow ) _invWindow.reset( new gui::InventoryWindow(_engine) );

  _invWindow->show();
}

}
