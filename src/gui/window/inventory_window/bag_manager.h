#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <memory>
#include <amenu.h>
#include <asub_panel.h>
#include <body_manager.h>

namespace amarlon {
  class Actor;
  class Engine;
namespace gui {

class BagManager : public ASubPanel
{
public:
  BagManager(int w, int h);

  void manage();
  void fillBag();
  void selectNext();
  void selectPrevious();
  void activate();
  void deactivate();

private:
  enum ItemOperation
  {
    INVALID,
    DROP,
    EQUIP,
    INSPECT
  };

  AMenuPtr _bagMenu;

  void drop(ActorPtr item);
  bool handleStackableDrop(ActorPtr item);

  void equip(ActorPtr item);
  bool canEquip(ItemSlotType slot);
  void doTheEquip(ActorPtr item);
  ItemOperation chooseItemOperationFromMenu(ActorPtr selected);
  int getAmountToDrop(ActorPtr toDrop);

};

typedef std::shared_ptr<BagManager> BagManagerPtr;

}}

#endif // INVENTORY_MANAGER_H
