#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include <memory>
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
   *        If move outside map borders, then Map::onExit is called with proper direction
   * @return True if path was not blocked, false otherwise
   */
  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

protected:
  int _dx;
  int _dy;
  ActorPtr _performer;

  bool patchIsBlocked();

};

typedef std::shared_ptr<MoveAction> MoveActionPtr;
typedef std::unique_ptr<MoveAction> MoveActionUPtr;

}

#endif // MOVE_ACTION_H
