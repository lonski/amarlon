#include "slot_menu_item.h"

namespace amarlon { namespace gui {

SlotMenuItem::SlotMenuItem(int width, const std::string &name)
  : _panel(width, 5)
  , _frameColorTemp(_panel.getFrameColor())
  , _slotName(new Label)
  , _slotValue(new Label)
{
  _panel.setFrameColor(TCODColor::darkYellow);

  InitalizeNameLabel(name);
  initalizeValueLabel();
  initalizeSeparator();
}

void SlotMenuItem::InitalizeNameLabel(const std::string &name)
{
  _slotName->setPosition(2,2);
  _slotName->setValue(name);
  _panel.addWidget(_slotName);
}

void SlotMenuItem::initalizeValueLabel()
{
  _slotValue->setPosition( _panel.getWidth() / 3, 2 );
  _slotValue->setColor(TCODColor::lightChartreuse);
  _frameColorTemp = _panel.getFrameColor();
  _panel.addWidget(_slotValue);
}

void SlotMenuItem::initalizeSeparator()
{
  Label* sep = new Label;
  sep->setValue(":");
  sep->setPosition( _panel.getWidth() / 3 - 2, 2 );
  _panel.addWidget(sep);
}

void SlotMenuItem::setSlotName(const std::string &name)
{
  _slotName->setValue(name);
}

std::string SlotMenuItem::getSlotName()
{
  return _slotName->getValue();
}

void SlotMenuItem::setSlotValue(const std::string &value)
{
  _slotValue->setValue(value);
}

std::string SlotMenuItem::getSlotValue()
{
  return _slotValue->getValue();
}

void SlotMenuItem::select()
{
  if ( !_selected )
  {
    _panel.setFrameColor( _frameColorTemp * 1.9 );
    _selected = true;
  }
}

void SlotMenuItem::deselect()
{
  if ( _selected )
  {
    _panel.setFrameColor( _frameColorTemp );
    _selected = false;
  }
}

void SlotMenuItem::render(TCODConsole &console)
{
  _panel.setPosition( getX(), getY() );
  _panel.render(console);
}

}}
