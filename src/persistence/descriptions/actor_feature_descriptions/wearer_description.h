#ifndef WEARER_DESCRIPTION
#define WEARER_DESCRIPTION

#include <description.h>
#include <vector>

namespace amarlon {

struct ActorDescription;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

struct WearerDescription : Description
{
  std::vector<int> itemSlots;
  std::vector<ActorDescriptionPtr> eqItems;
};

typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;

}

#endif // WEARER_DESCRIPTION

