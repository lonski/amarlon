#include "CmdInventory.h"
#include <iostream>
#include <algorithm>
#include <Engine.h>
#include <Gui/Window/InventoryWindow/inventory_window.h>

namespace amarlon {

CmdInventory::CmdInventory()
{
}

bool CmdInventory::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'i' );
}

void CmdInventory::execute(Actor*)
{
  Engine::instance().windowManager()
                    .getWindow<gui::InventoryWindow>()
                    .show();
}

}
