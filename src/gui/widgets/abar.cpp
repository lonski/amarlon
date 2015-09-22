#include "abar.h"

namespace amarlon { namespace gui {

ABar::ABar()  
  : _value(0)
  , _maxValue(10)
  , _bgColor(TCODColor::darkerRed)
  , _fgColor(TCODColor::red)
  , _displayValues(true)
  , _textColor(TCODColor::white)
  , _width(10)
  , _height(3)
{  
}

void ABar::render(TCODConsole &console)
{
    // fill the background
    console.setDefaultBackground(_bgColor);
    console.rect(getX(),getY(), _width, _height, false, TCOD_BKGND_SET);

    // draw the bar
    int barWidth = static_cast<int>(_value / _maxValue * _width);
    if ( barWidth > 0 )
    {
      console.setDefaultBackground(_fgColor);
      console.rect(getX(), getY(), barWidth, _height, false, TCOD_BKGND_SET);
    }

    // print text on top of the bar
    console.setDefaultForeground(_textColor);

    if ( _displayValues )
      console.printEx(getX()+_width/2, getY()+1, TCOD_BKGND_NONE,TCOD_CENTER,
                      "%s%g/%g", _name.empty() ? "" : (_name + " : ").c_str(), _value, _maxValue);
    else
      console.printEx(getX()+_width/2, getY()+1, TCOD_BKGND_NONE,TCOD_CENTER,	"%s", _name.c_str());

}

std::string ABar::getName() const
{
  return _name;
}

void ABar::setName(const std::string &name)
{
  _name = name;
}
float ABar::getValue() const
{
  return _value;
}

void ABar::setValue(float value)
{
  _value = value;
}
float ABar::getMaxValue() const
{
  return _maxValue;
}

void ABar::setMaxValue(float maxValue)
{
  _maxValue = maxValue;
}
TCODColor ABar::getBgColor() const
{
  return _bgColor;
}

void ABar::setBgColor(const TCODColor &bgColor)
{
  _bgColor = bgColor;
}
TCODColor ABar::getFgColor() const
{
  return _fgColor;
}

void ABar::setFgColor(const TCODColor &fgColor)
{
  _fgColor = fgColor;
}
bool ABar::displayValues() const
{
  return _displayValues;
}

void ABar::setDisplayValues(bool displayValues)
{
  _displayValues = displayValues;
}
TCODColor ABar::getTextColor() const
{
  return _textColor;
}

void ABar::setTextColor(const TCODColor &textColor)
{
  _textColor = textColor;
}

int ABar::getWidth() const
{
  return _width;
}

int ABar::getHeight() const
{
  return _height;
}

void ABar::setWidth(int width)
{
  _width = width;
}

void ABar::setHeight(int height)
{
  _height = height;
}

}}

