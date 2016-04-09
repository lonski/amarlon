#ifndef TELEPORT_ACTION_H
#define TELEPORT_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class TeleportAction : public ActorAction
{
public:
  TeleportAction(int map, int x, int y);
  virtual ~TeleportAction();

  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

  virtual int getMapId() const;
  virtual int getX() const;
  virtual int getY() const;

  virtual DescriptionPtr toDescriptionStruct();

private:
  int _map;
  int _x;
  int _y;

  void removeFromCurrentMap(ActorPtr performer);

};

typedef std::shared_ptr<TeleportAction> TeleportActionPtr;\
typedef std::unique_ptr<TeleportAction> TeleportActionUPtr;

}

#endif // TELEPORT_ACTION_H
