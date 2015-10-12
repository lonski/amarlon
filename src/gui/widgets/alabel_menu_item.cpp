#include "alabel_menu_item.h"
#include <alabel.h>

namespace amarlon { namespace gui {

ALabelMenuItem::ALabelMenuItem()
  : _label(new ALabel)
  , _selected(false)
{  
  setColor(TCODColor::lightChartreuse);
}

ALabelMenuItem::ALabelMenuItem(const std::string &text)
  : _label(new ALabel)
  , _selected(false)
{
  setValue(text);
  setColor(TCODColor::lightChartreuse);
}

void ALabelMenuItem::render(TCODConsole &console)
{
  _label->setPosition( getX(), getY() );
  _label->render(console);
}

void ALabelMenuItem::select()
{
  if (!_selected)
  {
    TCODColor temp = _label->getBgcolor();

    _label->setBgcolor( _label->getColor() );
    _label->setColor( temp );

    _selected = true;
  }
}

void ALabelMenuItem::deselect()
{
  if (_selected)
  {
    TCODColor temp = _label->getColor();

    _label->setColor( _label->getBgcolor() );
    _label->setBgcolor( temp );

    _selected = false;
  }
}

bool ALabelMenuItem::isSelected() const
{
  return _selected;
}

std::string ALabelMenuItem::getValue() const
{
  return _label->getValue();
}

void ALabelMenuItem::setValue(const std::string &value)
{
  _label->setValue(value);
}

int ALabelMenuItem::getWidth() const
{
  return _label->getWidth();
}

int ALabelMenuItem::getHeight() const
{
  return _label->getHeight();
}

void ALabelMenuItem::setWidth(int width)
{
  _label->setWidth(width);
}

void ALabelMenuItem::setHeight(int height)
{
  _label->setHeight(height);
}

TCODColor ALabelMenuItem::getColor() const
{
  return _label->getColor();
}

void ALabelMenuItem::setColor(const TCODColor &color)
{
  _label->setColor(color);
}

}}

