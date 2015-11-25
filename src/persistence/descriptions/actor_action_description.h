#ifndef ACTOR_ACTION_DESCRIPTION
#define ACTOR_ACTION_DESCRIPTION

#include <memory>

namespace amarlon {

struct ActorActionDescription
{
  int teleport_MapId;
  int teleport_x;
  int teleport_y;
};

typedef std::shared_ptr<ActorActionDescription> ActorActionDescriptionPtr;

}

#endif // ACTOR_ACTION_DESCRIPTION

