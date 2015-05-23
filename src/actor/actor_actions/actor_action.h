#ifndef ACTOR_ACTION
#define ACTOR_ACTION

#include <memory>

namespace amarlon{

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

/**
 * @brief Generic operation that can be performed on any Actor (Player, Mob or Item)
 */
class ActorAction
{
public:
  ActorAction() = default;
  virtual ~ActorAction() {}

  virtual bool perform(ActorPtr actor) = 0;
};

typedef std::shared_ptr<ActorAction> ActorActionPtr;

}

#endif // ACTOR_ACTION

