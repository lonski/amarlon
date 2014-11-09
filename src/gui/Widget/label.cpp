#include "label.h"

namespace amarlon { namespace gui {

Label::Label()
  : _color(TCODColor::white)
  , _bgcolor(TCODColor::black)
  , _aligment(TCOD_LEFT)
{
}

void Label::render(TCODConsole &console)
{
  console.setDefaultForeground(_color);
  console.setDefaultBackground(_bgcolor);
  console.printEx(_x, _y,
                  TCOD_BKGND_SET,
                  _aligment, "%s", _value.c_str());

  setWidth(_value.size());
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
TCOD_alignment_t Label::getAligment() const
{
  return _aligment;
}

void Label::setAligment(const TCOD_alignment_t &aligmnet)
{
  _aligment = aligmnet;
}
TCODColor Label::getBgcolor() const
{
  return _bgcolor;
}

void Label::setBgcolor(const TCODColor &bgColor)
{
  _bgcolor = bgColor;
}





}}
