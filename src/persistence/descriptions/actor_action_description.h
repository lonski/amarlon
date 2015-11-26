#ifndef ACTOR_ACTION_DESCRIPTION
#define ACTOR_ACTION_DESCRIPTION

#include <memory>
#include <description.h>

namespace amarlon {

struct ActorActionDescription : Description
{
  int teleport_MapId;
  int teleport_x;
  int teleport_y;
};

typedef std::shared_ptr<ActorActionDescription> ActorActionDescriptionPtr;

}

#endif // ACTOR_ACTION_DESCRIPTION

