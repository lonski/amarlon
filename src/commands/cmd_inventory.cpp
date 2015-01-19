#include "cmd_inventory.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include "engine.h"
#include "gui/window/inventory_window/inventory_window.h"

namespace amarlon {

CmdInventory::CmdInventory()
{
}

bool CmdInventory::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'i' );
}

void CmdInventory::execute()
{
  Engine::instance().windowManager()
                    .getWindow<gui::InventoryWindow>()
                    .show();
}

}
