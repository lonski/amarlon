#include "awidget.h"
#include <engine.h>

namespace amarlon { namespace gui {

AWidget::AWidget(const int &w, const int &h)
  : _x(0)
  , _y(0)
  , _width(w)
  , _height(h)
{
}

int AWidget::getX() const
{
  return _x;
}
int AWidget::getY() const
{
  return _y;
}

void AWidget::setPosition(int x, int y)
{
  _x = x;
  _y = y;
}

void AWidget::setPosition(AWidget::PositionFlag position)
{
  switch ( position )
  {
    case WINDOW_CENTER:
    {
      setPosition( Engine::screenWidth / 2 - getWidth() / 2,
                   Engine::screenHeight / 2 - getHeight() / 2);
      break;
    }
  case GAME_SCREEN_CENTER:
    {
      setPosition( Engine::consoleWidth / 2 - getWidth() / 2,
                   Engine::consoleHeight / 2 - getHeight() / 2);
      break;
    }
  }
}

std::string AWidget::getTag(const std::string &tagName)
{
  auto tag = _tags.find(tagName);
  return tag == _tags.end() ? "" : tag->second;
}

void AWidget::setTag(const std::string &tagName, const std::string &tagValue)
{
  _tags[tagName] = tagValue;
}
int AWidget::getWidth() const
{
  return _width;
}

void AWidget::setWidth(int width)
{
  _width = width;
}
int AWidget::getHeight() const
{
  return _height;
}

void AWidget::setHeight(int height)
{
  _height = height;
}

}}
