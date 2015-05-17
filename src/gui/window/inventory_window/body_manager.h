#ifndef BODY_MANAGER_H
#define BODY_MANAGER_H

#include <memory>
#include <string>
#include <item_slot_type.h>
#include <inventory_panel.h>
#include <amenu.h>

namespace amarlon {
  class Actor;
namespace gui {

class BodyManager : public AInventoryPanel
{
public:  
  BodyManager(int w, int h);

  void manage();
  void fillBodySlots();
  void selectNext();
  void selectPrevious();
  void activate();
  void deactivate();

private:
  AMenuPtr _bodyMenu;

  Actor *chooseItemToEquip(ItemSlotType slot);
  bool equipItem(Actor* toEquip);
  std::vector<Actor*> getEquipableItemsList(ItemSlotType slot);
  bool unequipItem(ItemSlotType slot);

};

typedef std::shared_ptr<BodyManager> BodyManagerPtr;

}}

#endif // BODY_MANAGER_H
