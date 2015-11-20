#ifndef PICKUP_ACTION_H
#define PICKUP_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon{

class Inventory;
typedef std::shared_ptr<Inventory> InventoryPtr;

class PickUpAction : public ActorAction
{
public:
  /**
   * @brief Makes actor pick up an item, and put it into inventory.
   * @param toPick - actor to be picked up
   * @param amount - usable if item is stackable, if not provided then max amount is picked up
   * @param removeAction - function will be called to remove whole actor from source container
   */
  PickUpAction(ActorPtr toPick, int amount = -1, std::function<void(ActorPtr)> removeAction = [](ActorPtr){});
  virtual ~PickUpAction();

  /**
   * @return True if picked up successfully. If performer has no container, or there is
   *         no space left, then false.
   */
  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _toPick;
  int _amount;
  ActorPtr _performer;
  std::function<void(ActorPtr)> _removeAction;

  ActorActionResult pickUpAll();
  ActorActionResult pickUpAmount();

};

typedef std::shared_ptr<PickUpAction> PickUpActionPtr;
typedef std::unique_ptr<PickUpAction> PickUpActionUPtr;

}

#endif // PICKUP_ACTION_H
