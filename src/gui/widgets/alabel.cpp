#include "alabel.h"

namespace amarlon { namespace gui {

ALabel::ALabel()
  : _color(TCODColor::white)
  , _bgcolor(TCODColor::black)
  , _autosize(true)
{
}

void ALabel::render(TCODConsole &console)
{
  console.setDefaultForeground(_color);
  console.setDefaultBackground(_bgcolor);
  console.printEx(_x, _y,
                  TCOD_BKGND_SET,
                  TCOD_LEFT, "%s", _value.c_str());

  if ( _autosize ) setWidth(_value.size());
}
std::string ALabel::getValue() const
{
  return _value;
}

void ALabel::setValue(const std::string &value)
{
  _value = value;
}
TCODColor ALabel::getColor() const
{
  return _color;
}

void ALabel::setColor(const TCODColor &color)
{
  _color = color;
}

TCODColor ALabel::getBgcolor() const
{
  return _bgcolor;
}

void ALabel::setBgcolor(const TCODColor &bgColor)
{
  _bgcolor = bgColor;
}
bool ALabel::isAutosized() const
{
  return _autosize;
}

void ALabel::setAutosize(bool autosize)
{
  _autosize = autosize;
}






}}
