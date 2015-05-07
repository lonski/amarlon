#include "abar.h"

namespace amarlon { namespace gui {

ABar::ABar()
  : AWidget(10, 3)
  , _value(0)
  , _maxValue(10)
  , _bgColor(TCODColor::darkerRed)
  , _fgColor(TCODColor::red)
  , _displayValues(true)
  , _textColor(TCODColor::white)
{
}

void ABar::render(TCODConsole &console)
{
    // fill the background
    console.setDefaultBackground(_bgColor);
    console.rect(_x,_y, _width, _height,false,TCOD_BKGND_SET);

    // draw the bar
    int barWidth = static_cast<int>(_value / _maxValue * _width);
    if ( barWidth > 0 )
    {
      console.setDefaultBackground(_fgColor);
      console.rect(_x, _y, barWidth, _height, false, TCOD_BKGND_SET);
    }

    // print text on top of the bar
    console.setDefaultForeground(_textColor);

    if ( _displayValues )
      console.printEx(_x+_width/2, _y+1, TCOD_BKGND_NONE,TCOD_CENTER,
                      "%s%g/%g", _name.empty() ? "" : (_name + " : ").c_str(), _value, _maxValue);
    else
      console.printEx(_x+_width/2, _y+1, TCOD_BKGND_NONE,TCOD_CENTER,	"%s", _name.c_str());

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

}}
