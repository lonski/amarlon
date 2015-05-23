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

bool MoveAction::perform(ActorPtr performer)
{
  bool moved = false;
  _performer = performer;

  if ( _performer && !patchIsBlocked() )
  {
    performer->setPosition( performer->getX() + _dx, performer->getY() + _dy );
    moved = true;
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
