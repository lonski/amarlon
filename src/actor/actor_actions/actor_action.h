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

  virtual ActorActionUPtr clone() = 0;

  /**
   * @brief Starts executing the action. Sets isRunning to true
   * @param Actor who is performing the action
   */
  virtual bool run(ActorPtr performer) = 0;

  /**
   * @brief The amount of Action Points needed to perform the action. One Action Point is equal to one Game Tick
   */
  virtual int getActionPointCount() const { return 1; }

  /**
   * @return True if action has been executed, but not yet finished
   */
  virtual bool isRunning() const { return false; }

  /**
   * @brief Triggers time. Decrementrs the game ticks still needed to finish the action by 1.
   */
  virtual void tick() {}

};

}

#endif // ACTOR_ACTION

