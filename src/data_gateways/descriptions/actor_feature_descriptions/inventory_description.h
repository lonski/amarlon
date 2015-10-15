#ifndef INVENTORY_DESCRIPTION
#define INVENTORY_DESCRIPTION

#include <description.h>
#include <actor_type.h>
#include <vector>

namespace amarlon {

struct ActorDescription;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

struct InventoryDescription : Description
{
  InventoryDescription() : maxSize(0) {}

  size_t maxSize;
  std::vector<ActorDescriptionPtr> content;
};

typedef std::shared_ptr<InventoryDescription> InventoryDescriptionPtr;

}

#endif // INVENTORY_DESCRIPTION

