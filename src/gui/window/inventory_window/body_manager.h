#ifndef BODY_MANAGER_H
#define BODY_MANAGER_H

#include <memory>
#include <gui/widget/menu/menu.h>
#include <Actor/ActorFeatures/wearer/item_slot_type.h>

namespace amarlon {
  class Actor;
namespace gui {

class BodyManager
{
public:
  BodyManager(MenuPtr _bodyMenu);

  void manage();
  void fillBodySlots();

  void clearSelectedItemSlotValue();
  std::vector<Actor *> getEquipableItemsList(ItemSlotType slot);
  void equipItem(Actor* toEquip);
private:
  MenuPtr _bodyMenu;

  void unequipItem(ItemSlotType slot);
  void chooseAndEquipItem(ItemSlotType slot);

};

typedef std::shared_ptr<BodyManager> BodyManagerPtr;

}}

#endif // BODY_MANAGER_H
