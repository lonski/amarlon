#include "label_menu_item.h"

namespace amarlon { namespace gui {

LabelMenuItem::LabelMenuItem()
{
}

void LabelMenuItem::render(TCODConsole &console)
{
  _label.setPosition( getX(), getY() );
  _label.render(console);
}

void LabelMenuItem::select()
{
  TCODColor temp = _label.getBgcolor();

  _label.setBgcolor( _label.getColor() );
  _label.setColor( temp );

  _selected = true;
}

void LabelMenuItem::deselect()
{
  TCODColor temp = _label.getColor();

  _label.setColor( _label.getBgcolor() );
  _label.setBgcolor( temp );

  _selected = false;
}

std::string LabelMenuItem::getValue() const
{
  return _label.getValue();
}

void LabelMenuItem::setValue(const std::string &value)
{
  _label.setValue(value);
}

TCODColor LabelMenuItem::getColor() const
{
  return _label.getColor();
}

void LabelMenuItem::setColor(const TCODColor &color)
{
  _label.setColor(color);
}

}}
