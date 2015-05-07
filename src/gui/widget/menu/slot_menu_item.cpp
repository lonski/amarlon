#include "slot_menu_item.h"
#include <alabel.h>
#include <abar.h>

namespace amarlon { namespace gui {


SlotMenuItem::SlotMenuItem(int width, const std::string &name)
  : _panel(width, 5)
  , _background(new ABar)
  , _slotName(new ALabel)
  , _slotValue(new ALabel)
{
  setHeight( _panel.getHeight() );
  setWidth( _panel.getWidth() );

  _panel.setFrameColor(TCODColor::darkYellow);

  InitalizeNameLabel(name);
  initalizeValueLabel();
  initalizeSeparator();
  initalizebackground();
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
  _panel.addWidget(_slotValue);
}

void SlotMenuItem::initalizeSeparator()
{
  ALabel* sep = new ALabel;
  sep->setValue(":");
  sep->setPosition( _panel.getWidth() / 3 - 2, 2 );
  _panel.addWidget(sep);
}

void SlotMenuItem::initalizebackground()
{
  _background->setPosition(1,1);
  _background->setDisplayValues(false);
  _background->setWidth( _panel.getWidth() - 2 );
  _background->setHeight( _panel.getHeight() - 2 );
  _background->setBgColor( TCODColor::black );
  _panel.addWidget( _background );
}

void SlotMenuItem::setSlotName(const std::string &name)
{
  _slotName->setValue(name);
}

std::string SlotMenuItem::getSlotName()
{
  return _slotName->getValue();
}

void SlotMenuItem::setValue(const std::string &value)
{
  _slotValue->setValue(value);
}

std::string SlotMenuItem::getValue()
{
  return _slotValue->getValue();
}

void SlotMenuItem::select()
{
  if ( !_selected )
  {
    _background->setBgColor( _panel.getFrameColor() * 0.2 );
    _selected = true;
  }
}

void SlotMenuItem::deselect()
{
  if ( _selected )
  {
    _background->setBgColor( TCODColor::black );
    _selected = false;
  }
}

void SlotMenuItem::render(TCODConsole &console)
{
  _panel.setPosition( getX(), getY() );
  _panel.render(console);
}

}}
