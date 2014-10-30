#include "CmdInventory.h"
#include <iostream>
#include <algorithm>
#include <Gui/InventoryManager/inventory_window.h>

namespace amarlon {

CmdInventory::CmdInventory()
{
}

bool CmdInventory::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'i' );
}

void CmdInventory::execute(Engine* engine, Actor*)
{  
  if ( !_invWindow ) _invWindow.reset( new gui::InventoryWindow(engine) );

  _invWindow->show();
}

}
