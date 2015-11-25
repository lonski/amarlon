#ifndef ACTOR_ACTION
#define ACTOR_ACTION

#include <memory>
#include <actor_action_result.h>

namespace amarlon{

class Actor;
class ActorAction;
struct ActorActionDescription;
typedef std::shared_ptr<ActorActionDescription> ActorActionDescriptionPtr;
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

  virtual ActorActionResult perform(ActorPtr performer) = 0;
  virtual ActorActionUPtr clone() = 0;

  virtual ActorActionDescriptionPtr toDescriptionStruct()
  {
    throw std::logic_error("ActorAction::toDescriptionStruct not implemented!");
    return nullptr;
  }

};

}

#endif // ACTOR_ACTION

