#ifndef WEARER_DESCRIPTION
#define WEARER_DESCRIPTION

#include <description.h>
#include <vector>
#include <item_slot_type.h>
#include <inventory_description.h>

namespace amarlon {

struct InventoryDescription;

struct WearerDescription : Description
{
  WearerDescription()
    :
      //TODO remove the init here to lower the dependency
      //move it to WearerDescription use place
    eqItems( new InventoryDescription )
  {}

  std::vector<ItemSlotType> itemSlots;
  std::shared_ptr<InventoryDescription> eqItems;
};

typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;

}

#endif // WEARER_DESCRIPTION

