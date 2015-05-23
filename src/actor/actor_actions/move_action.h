#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include <actor_action.h>

namespace amarlon{

class Map;
typedef std::shared_ptr<Map> MapPtr;

class MoveAction : public ActorAction
{
public:
  MoveAction(int dx, int dy);
  virtual ~MoveAction();

  /**
   * @brief Moves actor for given coordinate difference. Check if path is blocked.
   * @return True if path was not blocked, false otherwise
   */
  virtual bool perform(ActorPtr performer);

private:
  int _dx;
  int _dy;
  ActorPtr _performer;

  bool patchIsBlocked();

};

typedef std::shared_ptr<MoveAction> MoveActionPtr;

}

#endif // MOVE_ACTION_H
