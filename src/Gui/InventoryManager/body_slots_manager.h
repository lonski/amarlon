#ifndef BODY_SLOTS_MANAGER_H
#define BODY_SLOTS_MANAGER_H

#include <map>
#include <Gui/InventoryManager/body_slot.h>
#include <Actor/ActorFeatures/Wearer/item_slot_type.h>

namespace amarlon { namespace gui {

class BodySlotsManager : public Panel
{
public:
  BodySlotsManager(int w, int h);

  void addSlot(const std::string& name, ItemSlotType type, const std::string& value = "");
  BodySlotPtr getSlot(ItemSlotType type);

  int getMargin() const { return _margin; }
  void setMargin(int margin) { _margin = margin; }

private:
  std::map<ItemSlotType, BodySlotPtr> _slots;
  int _margin;

};

}}

#endif // BODY_SLOTS_MANAGER_H
