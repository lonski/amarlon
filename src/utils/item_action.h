#ifndef ITEMPICKER_H
#define ITEMPICKER_H
#include <memory>

namespace amarlon {

class Actor;
class Container;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Container> ContainerPtr;

class ItemAction
{
public:
  ItemAction(ActorPtr executor, ActorPtr targetItem, ContainerPtr sourceContainer = nullptr);

  /**
   * @brief Invokes the picking. Handles stackable and ask player for the amount to be picked.
   * @return The amount of items picked. If not staskable, then max amount is equal to 1.
   */
  int pick();

  /**
   * @brief Invokes dropping the item. Handles stackable and ask player for the amount to be picked.
   * @return The amount of items droped. If not staskable, then max amount is equal to 1.
   */
  int drop();

private:
  ActorPtr _executor;
  ActorPtr _targetItem;
  ContainerPtr _sourceFrom;

  void pickUpAll();
  int askForAmount(int defaultAmount);
  void dropOnMap(ActorPtr item);

};

}

#endif // ITEMPICKER_H
