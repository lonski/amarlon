#include "bar.h"

namespace amarlon { namespace gui {

Bar::Bar()
  : _width(10)
  , _value(0)
  , _maxValue(10)
  , _bgColor(TCODColor::darkerRed)
  , _fgColor(TCODColor::red)
  , _displayValues(true)
  , _textColor(TCODColor::white)
{
}

void Bar::render(TCODConsole &console)
{
    // fill the background
    console.setDefaultBackground(_bgColor);
    console.rect(_x,_y,_width,3,false,TCOD_BKGND_SET);

    // draw the bar
    int barWidth = static_cast<int>(_value / _maxValue * _width);
    if ( barWidth > 0 )
    {
      console.setDefaultBackground(_fgColor);
      console.rect(_x, _y, barWidth, 3, false, TCOD_BKGND_SET);
    }

    // print text on top of the bar
    console.setDefaultForeground(_textColor);

    if ( _displayValues )
      console.printEx(_x+_width/2, _y+1, TCOD_BKGND_NONE,TCOD_CENTER,
                      "%s%g/%g", _name.empty() ? "" : (_name + " : ").c_str(), _value, _maxValue);
    else
      console.printEx(_x+_width/2, _y+1, TCOD_BKGND_NONE,TCOD_CENTER,	"%s", _name.c_str());

}

int Bar::getWidth() const
{
  return _width;
}

void Bar::setWidth(int width)
{
  _width = width;
}
std::string Bar::getName() const
{
  return _name;
}

void Bar::setName(const std::string &name)
{
  _name = name;
}
float Bar::getValue() const
{
  return _value;
}

void Bar::setValue(float value)
{
  _value = value;
}
float Bar::getMaxValue() const
{
  return _maxValue;
}

void Bar::setMaxValue(float maxValue)
{
  _maxValue = maxValue;
}
TCODColor Bar::getBgColor() const
{
  return _bgColor;
}

void Bar::setBgColor(const TCODColor &bgColor)
{
  _bgColor = bgColor;
}
TCODColor Bar::getFgColor() const
{
  return _fgColor;
}

void Bar::setFgColor(const TCODColor &fgColor)
{
  _fgColor = fgColor;
}
bool Bar::displayValues() const
{
  return _displayValues;
}

void Bar::setDisplayValues(bool displayValues)
{
  _displayValues = displayValues;
}
TCODColor Bar::getTextColor() const
{
  return _textColor;
}

void Bar::setTextColor(const TCODColor &textColor)
{
  _textColor = textColor;
}











}}