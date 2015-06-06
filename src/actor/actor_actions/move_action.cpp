#include "move_action.h"
#include <actor.h>
#include <map.h>

namespace amarlon{

MoveAction::MoveAction(int dx, int dy)
  : _actionPoints(1)
  , _dx(dx)
  , _dy(dy)
  , _running(false)
{
  _ticksLeft = _actionPoints;
}

MoveAction::~MoveAction()
{
}

ActorActionUPtr MoveAction::clone()
{
  MoveActionUPtr cloned = std::make_unique<MoveAction>(_dx,_dy);
  cloned->_performer = _performer;

  return std::move(cloned);
}

int MoveAction::getActionPointCount() const
{
  return _actionPoints;
}

bool MoveAction::isRunning() const
{
  return _running;
}

bool MoveAction::run(ActorPtr performer)
{  
  if ( !isRunning() )
  {
    _performer = performer;
    _ticksLeft = _actionPoints;
    _running = true;

    return true;
  }
  return false;
}

void MoveAction::tick()
{
  if ( isRunning() )
  {
    if ( --_ticksLeft <= 0 )
    {
      perform();
      _running = false;
    }
  }
}

bool MoveAction::perform()
{
  bool moved = false;

  if ( _performer )
  {
    int newX = _performer->getX() + _dx;
    int newY = _performer->getY() + _dy;

    MapPtr map = _performer->getMap();
    if ( map )
    {
      moved = true;
      if ( newX < 0 )
      {
        map->onExit(Direction::West, _performer);
      }
      else if ( newX >= static_cast<int>(map->getWidth()) )
      {
        map->onExit(Direction::East, _performer);
      }
      else if ( newY < 0 )
      {
        map->onExit(Direction::North, _performer);
      }
      else if ( newY >= static_cast<int>(map->getHeight()) )
      {
        map->onExit(Direction::South, _performer);
      }
      else
      {
        if ( !patchIsBlocked() )
        {
          _performer->setPosition( newX, newY );
        }
        else
        {
          moved = false;
        }
      }

    }
  }

  return moved;
}

bool MoveAction::patchIsBlocked()
{
  bool blocked = false;
  MapPtr map = _performer->getMap();
  if ( map )
  {
    int targetX = _performer->getX() + _dx;
    int targetY = _performer->getY() + _dy;
    blocked = map->isBlocked(targetX, targetY);
  }

  return blocked;
}

}
