#ifndef INVENTORY_DESCRIPTION
#define INVENTORY_DESCRIPTION

#include <description.h>
#include <vector>
#include <experimental/optional>

namespace amarlon {

struct ActorDescription;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

struct InventoryDescription : Description
{
  std::experimental::optional<size_t> maxSize;
  std::vector<ActorDescriptionPtr> content;
};

typedef std::shared_ptr<InventoryDescription> InventoryDescriptionPtr;

}

#endif // INVENTORY_DESCRIPTION

