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
  virtual ActorActionUPtr clone();

private:
  MapId _map;
  int _x;
  int _y;

  void removeFromCurrentMap(ActorPtr performer);

};

typedef std::shared_ptr<TeleportAction> TeleportActionPtr;\
typedef std::unique_ptr<TeleportAction> TeleportActionUPtr;

}

#endif // TELEPORT_ACTION_H
