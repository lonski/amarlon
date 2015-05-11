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

  void clearSelectedItemSlotValue();
  std::vector<Actor *> getEquipableItemsList(ItemSlotType slot);
  void equipItem(Actor* toEquip);
  AMenuItemPtr getSelectedItem();
  void selectNext();
  void selectPrevious();
  void activate();
  void deactivate();
  bool setSlotValue(ItemSlotType slot, const std::string& value);

private:
  AMenuPtr _bodyMenu;

  void unequipItem(ItemSlotType slot);
  void chooseAndEquipItem(ItemSlotType slot);

};

typedef std::shared_ptr<BodyManager> BodyManagerPtr;

}}

#endif // BODY_MANAGER_H
