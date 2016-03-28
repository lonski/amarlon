#include "alabel.h"

namespace amarlon { namespace gui {

ALabel::ALabel()
  : _color(TCODColor::white)
  , _bgcolor(TCODColor::black)
  , _autosize(true)
  , _width(0)
  , _height(0)
{
}

void ALabel::render(TCODConsole &console)
{
  console.setDefaultForeground(_color);
  console.setDefaultBackground(_bgcolor);
  console.printEx(getX(), getY(),
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
  if ( _autosize )
  {
    _width = value.size();
  }
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

int ALabel::getWidth() const
{
  return _width;
}

int ALabel::getHeight() const
{
  return _autosize ? 1 : _height;
}

void ALabel::setWidth(int width)
{
  if ( !_autosize ) _width = width;
}

void ALabel::setHeight(int height)
{
  _height = height;
}

}}

