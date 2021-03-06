#include "cmd_inventory.h"
#include <memory>
#include <engine.h>
#include <inventory_window.h>

namespace amarlon {

CmdInventory::CmdInventory()
{
}

bool CmdInventory::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'I' );
}

int CmdInventory::execute()
{
  Engine::instance().getWindowManager()
                    .getWindow<gui::InventoryWindow>()
                    .show();
  return 1;
}

}

