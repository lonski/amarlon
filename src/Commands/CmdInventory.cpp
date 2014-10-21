#include "CmdInventory.h"
#include <iostream>
#include <algorithm>
#include "Utils/InventoryManager.h"

CmdInventory::CmdInventory()
{
}

bool CmdInventory::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'i' );
}

void CmdInventory::execute(Engine*, Actor *executor)
{
  if ( executor->afContainer() )
  {
    InventoryManager inv(executor);
    inv.setTitle("Inventory");
    inv.display();
  }
}
