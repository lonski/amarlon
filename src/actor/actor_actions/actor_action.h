#ifndef ACTOR_ACTION
#define ACTOR_ACTION

#include <memory>

namespace amarlon{

class Actor;
class ActorAction;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<ActorAction> ActorActionPtr;
typedef std::unique_ptr<ActorAction> ActorActionUPtr;

/**
 * @brief Generic operation that can be performed on any Actor (Player, Mob or Item)
 */
class ActorAction
{
public:
  ActorAction() = default;
  virtual ~ActorAction() {}

  virtual bool perform(ActorPtr performer) = 0;
  virtual ActorActionUPtr clone() = 0;

};

}

#endif // ACTOR_ACTION

