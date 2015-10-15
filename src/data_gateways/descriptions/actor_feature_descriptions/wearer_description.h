#ifndef WEARER_DESCRIPTION
#define WEARER_DESCRIPTION

#include <description.h>
#include <vector>
#include <item_slot_type.h>

namespace amarlon {

struct ActorDescription;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

struct WearerDescription : Description
{
  std::vector<ItemSlotType> itemSlots;
  std::vector<ActorDescriptionPtr> eqItems;
};

typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;

}

#endif // WEARER_DESCRIPTION

