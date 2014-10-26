#include "CmdInventory.h"
#include <iostream>
#include <algorithm>
#include "Utils/InventoryManager.h"

namespace amarlon {

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

  std::cout << "\n=======";
  if ( executor->afWearer() )
  {
  for(int s = (int)ItemSlotType::Null; s != (int)ItemSlotType::End; ++s)
    {
      ItemSlotType slot = (ItemSlotType)s;
      std::cout << "\nhas slot "<< s << " : " << executor->afWearer()->hasSlot(slot);
      std::cout << " eq = " << executor->afWearer()->equipped(slot);
    }
  }
  else std::cout << "\nNo wearer!\n";
}

}
