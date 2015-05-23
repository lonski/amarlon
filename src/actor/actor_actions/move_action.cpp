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

bool MoveAction::perform(ActorPtr actor)
{
  bool moved = false;
  _actor = actor;

  if ( _actor && !patchIsBlocked() )
  {
    actor->setPosition( actor->getX() + _dx, actor->getY() + _dy );
    moved = true;
  }

  return moved;
}

bool MoveAction::patchIsBlocked()
{
  bool blocked = false;  
  MapPtr map = _actor->getMap();
  if ( map )
  {    
    int targetX = _actor->getX() + _dx;
    int targetY = _actor->getY() + _dy;
    blocked = map->isBlocked(targetX, targetY);
  }

  return blocked;
}

}
