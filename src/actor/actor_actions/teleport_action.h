#ifndef TELEPORT_ACTION_H
#define TELEPORT_ACTION_H

#include <memory>
#include <actor_action.h>
#include <map_id.h>

namespace amarlon {

class TeleportAction : public ActorAction
{
public:
  TeleportAction(MapId map, int x, int y);
  virtual ~TeleportAction();

  virtual bool perform(ActorPtr performer);

private:
  MapId _map;
  int _x;
  int _y;

  void removeFromCurrentMap(ActorPtr performer);

};

typedef std::shared_ptr<TeleportAction> TeleportActionPtr;

}

#endif // TELEPORT_ACTION_H
