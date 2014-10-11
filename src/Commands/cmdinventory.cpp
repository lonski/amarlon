#include "cmdinventory.h"
#include <iostream>
#include <algorithm>
#include "Utils/InventoryManager.h"

CmdInventory::CmdInventory()
{
}

bool CmdInventory::accept(TCOD_key_t &key, Map *, Actor *executor)
{
  bool accepted = ( key.vk == TCODK_CHAR && key.c == 'i' );

  if (accepted)
  {
    if ( executor->afContainer )
    {
      InventoryManager inv(executor);
      inv.setTitle("Inventory");
      inv.display();
    }
  }

  return accepted;
}
