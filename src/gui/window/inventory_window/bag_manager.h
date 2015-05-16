#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <memory>
#include <amenu.h>
#include <inventory_panel.h>
#include <body_manager.h>

namespace amarlon {
  class Actor;
  class Engine;
namespace gui {

class BagManager : public AInventoryPanel
{
public:
  BagManager(BodyManager &body, int w, int h);

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
    EQUIP
  };

  AMenuPtr _bagMenu;
  BodyManager& _body;

  void render();

  void drop(Actor* item);
  bool handleStackableDrop(Actor*& item);

  void equip(Actor* item);
  bool canEquip(ItemSlotType slot);
  void doTheEquip(Actor* item);

  ItemOperation chooseItemOperationFromMenu(Actor* selected);

};

typedef std::shared_ptr<BagManager> BagManagerPtr;

}}

#endif // INVENTORY_MANAGER_H
