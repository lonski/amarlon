#include "move_action.h"
#include <actor.h>
#include <map.h>

namespace amarlon{

MoveAction::MoveAction(int dx, int dy)
  : _dx(dx)
  , _dy(dy)
{
}

MoveAction::~MoveAction()
{
}

ActorActionResult MoveAction::perform(ActorPtr performer)
{
  ActorActionResult r = ActorActionResult::Nok;
  _performer = performer;

  if ( _performer )
  {
    int newX = performer->getX() + _dx;
    int newY = performer->getY() + _dy;

    MapPtr map = performer->getMap();
    if ( map )
    {
      r = ActorActionResult::Ok;
      if ( newX < 0 )
      {
        map->onExit(Direction::West, performer);
      }
      else if ( newX >= static_cast<int>(map->getWidth()) )
      {
        map->onExit(Direction::East, performer);
      }
      else if ( newY < 0 )
      {
        map->onExit(Direction::North, performer);
      }
      else if ( newY >= static_cast<int>(map->getHeight()) )
      {
        map->onExit(Direction::South, performer);
      }
      else
      {
        if ( !patchIsBlocked() )
        {
          performer->setPosition( newX, newY );
        }
        else
        {
          r = ActorActionResult::Nok;
        }
      }

    }
  }

  return r;
}

ActorActionUPtr MoveAction::clone()
{
  MoveActionUPtr cloned = std::make_unique<MoveAction>(_dx,_dy);
  cloned->_performer = _performer;

  return std::move(cloned);
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

