#include "body_slots_manager.h"

namespace amarlon { namespace gui {

BodySlotsManager::BodySlotsManager(int w, int h)
  : Panel(w,h)
{
  setFrame(false);
}

void BodySlotsManager::addSlot(const std::string &name, ItemSlotType type, const std::string &value)
{
  BodySlotPtr newSlot( new BodySlot(getWidth() - 2*_margin, name) );
  newSlot->setSlotValue(value);
  newSlot->setPosition( _margin, _margin + _slots.size() * 5);
  _slots[type] = newSlot;
  addWidget(newSlot);
}

BodySlotPtr BodySlotsManager::getSlot(ItemSlotType type)
{
  return _slots.count(type) ? _slots[type] : BodySlotPtr();
}

}}
