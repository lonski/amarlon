#include "widget.h"
#include <Utils/glodef.h>

namespace amarlon { namespace gui {

Widget::Widget(const int &w, const int &h)
  : _x(0)
  , _y(0)
  , _width(w)
  , _height(h)
{
}

int Widget::getX() const
{
  return _x;
}
int Widget::getY() const
{
  return _y;
}

void Widget::setPosition(int x, int y)
{
  _x = x;
  _y = y;
}

void Widget::centerPosition()
{
 setPosition( gloScreenWidth / 2 - getWidth() / 2,
               gloScreenHeight / 2 - getHeight() / 2);
}

std::string Widget::getTag(const std::string &tagName)
{
  auto tag = _tags.find(tagName);
  return tag == _tags.end() ? "" : tag->second;
}

void Widget::setTag(const std::string &tagName, const std::string &tagValue)
{
  _tags[tagName] = tagValue;
}
int Widget::getWidth() const
{
  return _width;
}

void Widget::setWidth(int width)
{
  _width = width;
}
int Widget::getHeight() const
{
  return _height;
}

void Widget::setHeight(int height)
{
  _height = height;
}

}}
