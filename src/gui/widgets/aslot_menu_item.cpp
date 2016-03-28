#include "aslot_menu_item.h"
#include <alabel.h>
#include <abar.h>

namespace amarlon { namespace gui {

/*

  +-----------------------------------------------+
  |                                               |
  | SLOT_NAME : SLOT_VALUE                        |
  |                                               |
  +-----------------------------------------------+

*/

ASlotMenuItem::ASlotMenuItem(int width,
                             const std::string &name,
                             const std::string &value,
                             const std::string &separator,
                             TCODColor color)
  : _panel(width, 5)
  , _background(new ABar)
  , _slotName(new ALabel)
  , _slotValue(new ALabel)
  , _selected(false)
{
  _panel.setFrameColor(color);

  InitalizeNameLabel(name);
  initalizeValueLabel(value);
  initalizeSeparator(separator);
  initalizeBackground();
}

void ASlotMenuItem::InitalizeNameLabel(const std::string &name)
{
  _slotName->setPosition(2,2);
  _slotName->setValue(name);
  _panel.addWidget(_slotName);
}

void ASlotMenuItem::initalizeValueLabel(const std::string &value)
{
  _slotValue->setPosition( _panel.getWidth() / 3, 2 );
  _slotValue->setColor(TCODColor::lightChartreuse);
  _slotValue->setValue(value);
  _panel.addWidget(_slotValue);
}

void ASlotMenuItem::initalizeSeparator(const std::string &s)
{
  if ( !s.empty() )
  {
    ALabel* sep = new ALabel;
    sep->setValue(s);
    sep->setPosition( _panel.getWidth() / 3 - 2, 2 );
    _panel.addWidget(sep);
  }
}

void ASlotMenuItem::initalizeBackground()
{
  _background->setPosition(1,1);
  _background->setDisplayValues(false);
  _background->setWidth( _panel.getWidth() - 2 );
  _background->setHeight( _panel.getHeight() - 2 );
  _background->setBgColor( TCODColor::black );
  _panel.addWidget( _background );
}

void ASlotMenuItem::setName(const std::string &name)
{
  _slotName->setValue(name);
}

std::string ASlotMenuItem::getName()
{
  return _slotName->getValue();
}

void ASlotMenuItem::setHeight(int height)
{  
  _panel.setHeight(height);
}

void ASlotMenuItem::setWidth(int width)
{  
  _panel.setWidth(width);
}

int ASlotMenuItem::getHeight() const
{
  return _panel.getHeight();
}

int ASlotMenuItem::getWidth() const
{
  return _panel.getWidth();
}

void ASlotMenuItem::setValue(const std::string &value)
{
  _slotValue->setValue(value);
}

std::string ASlotMenuItem::getValue() const
{
  return _slotValue->getValue();
}

void ASlotMenuItem::select()
{
  if ( !_selected )
  {
    _background->setBgColor( _panel.getFrameColor() * 0.2 );
    _selected = true;
  }
}

void ASlotMenuItem::deselect()
{
  if ( _selected )
  {
    _background->setBgColor( TCODColor::black );
    _selected = false;
  }
}

bool ASlotMenuItem::isSelected() const
{
  return _selected;
}

TCODColor ASlotMenuItem::getColor() const
{
  return _slotValue->getColor();
}

void ASlotMenuItem::setColor(const TCODColor& color)
{
  _slotValue->setColor(color);
}

TCODColor ASlotMenuItem::getNameColor() const
{
  return _slotName->getColor();
}

void ASlotMenuItem::setNameColor(const TCODColor& c)
{
  _slotName->setColor(c);
}

void ASlotMenuItem::render(TCODConsole &console)
{
  _panel.setPosition( getX(), getY() );
  _panel.render(console);
}

}}

