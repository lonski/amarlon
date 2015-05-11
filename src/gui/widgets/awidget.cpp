#include "awidget.h"
#include <engine.h>

namespace amarlon { namespace gui {

AWidget::AWidget()
  : _x(0)
  , _y(0)  
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

}}
