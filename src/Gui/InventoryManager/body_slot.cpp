#include "body_slot.h"

namespace amarlon { namespace gui {

BodySlot::BodySlot(int width, const std::string &name)
  : Panel(width, 5)
  , _slotName(new Label)
  , _slotValue(new Label)
{
  setFrameColor(TCODColor::darkYellow);

  InitalizeNameLabel(name);
  initalizeValueLabel();
  initalizeSeparator();
}

void BodySlot::InitalizeNameLabel(const std::string &name)
{
  _slotName->setPosition(2,2);
  _slotName->setValue(name);
  addWidget(_slotName);
}

void BodySlot::initalizeValueLabel()
{
  _slotValue->setPosition( getWidth() / 3, 2 );
  _slotValue->setColor(TCODColor::lightChartreuse);
  addWidget(_slotValue);
}

void BodySlot::initalizeSeparator()
{
  Label* sep = new Label;
  sep->setValue(":");
  sep->setPosition( getWidth() / 3 - 2, 2 );
  addWidget(sep);
}

void BodySlot::setSlotName(const std::string &name)
{
  _slotName->setValue(name);
}

void BodySlot::setSlotValue(const std::string &value)
{
  _slotValue->setValue(value);
}


}}
