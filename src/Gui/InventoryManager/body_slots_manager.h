#ifndef BODY_SLOTS_MANAGER_H
#define BODY_SLOTS_MANAGER_H

#include <map>
#include <Gui/InventoryManager/body_slot.h>
#include <Actor/ActorFeatures/Wearer/item_slot_type.h>

namespace amarlon { namespace gui {

class BodySlotsManager : public Panel
{
public:
  BodySlotsManager(int w, int h) : Panel(w,h) { setFrame(false); }
  void addSlot(const std::string& name, ItemSlotType type, const std::string& value = "")
  {
    BodySlotPtr newSlot( new BodySlot(getWidth() - 2*_margin, name) );
    newSlot->setSlotValue(value);
    newSlot->setPosition( _margin, _margin + _slots.size() * 5);
    _slots[type] = newSlot;
    addWidget(newSlot);
  }

  BodySlotPtr getSlot(ItemSlotType type)
  {
    return _slots.count(type) ? _slots[type] : BodySlotPtr();
  }

  int getMargin() const { return _margin; }
  void setMargin(int margin) { _margin = margin; }

private:
  std::map<ItemSlotType, BodySlotPtr> _slots;
  int _margin;

};

}}

#endif // BODY_SLOTS_MANAGER_H
