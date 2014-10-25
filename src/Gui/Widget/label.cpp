#include "label.h"

namespace amarlon { namespace gui {

Label::Label()
  : _color(TCODColor::white)
{
}

void Label::render(TCODConsole &console)
{
  console.setDefaultForeground(_color);
  console.printEx(_x, _y, TCOD_BKGND_NONE,TCOD_LEFT, "%s", _value.c_str());
}
std::string Label::getValue() const
{
  return _value;
}

void Label::setValue(const std::string &value)
{
  _value = value;
}
TCODColor Label::getColor() const
{
  return _color;
}

void Label::setColor(const TCODColor &color)
{
  _color = color;
}



}}
