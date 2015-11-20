#ifndef DROP_ACTION_H
#define DROP_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class DropAction : public ActorAction
{
public:
  /**
   * @brief Drops an item on map.
   * @param amount - usable if item is stackable, if not entered, then whole item is dropped
   */
  DropAction(ActorPtr toDrop, int amount = -1);
  ~DropAction();

  /**
   * @brief If whole item is dropped, then item is also removed from the performer's inventory
   * @return True if dropped successfully.
   */
  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _toDrop;
  int _amount;
  ActorPtr _performer;

  void dropOnMap(ActorPtr item);

};

typedef std::shared_ptr<DropAction> DropActionPtr;
typedef std::unique_ptr<DropAction> DropActionUPtr;

}

#endif // DROP_ACTION_H
