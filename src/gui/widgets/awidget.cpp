#include "awidget.h"

namespace amarlon { namespace gui {

int AWidget::consoleWidth = 100;
int AWidget::consoleHeight = 60;
int AWidget::screenWidth = 120;
int AWidget::screenHeight = 75;

AWidget::AWidget()
  : _x(0)
  , _y(0)  
  , _parent(nullptr)
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

void AWidget::setY(int y)
{
  _y = y;
}

void AWidget::setX(int x)
{
  _x = x;
}

void AWidget::setPosition(AWidget::PositionFlag position)
{
  switch ( position )
  {
    case WINDOW_CENTER:
    {
      setPosition( AWidget::screenWidth / 2 - getWidth() / 2,
                   AWidget::screenHeight / 2 - getHeight() / 2);
      break;
    }
    case GAME_SCREEN_CENTER:
    {
      setPosition( AWidget::consoleWidth / 2 - getWidth() / 2,
                   AWidget::consoleHeight / 2 - getHeight() / 2);
      break;
    }
    case GAME_SCREEN_BOTTOM:
    {
      setPosition( AWidget::consoleWidth / 2 - getWidth() / 2,
                   AWidget::consoleHeight - getHeight());
      break;
    }
    case WINDOW_BOTTOM_LEFT:
    {
      setPosition( 0, AWidget::screenHeight - getHeight());
      break;
    }
  }
}

AWidget *AWidget::getParent() const
{
    return _parent;
}

void AWidget::setParent(AWidget *parent)
{
    _parent = parent;
}

}}

