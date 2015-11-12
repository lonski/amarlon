#include "move_to_target.h"
#include <ai.h>
#include <map.h>
#include <actor.h>
#include <monster_move_action.h>

namespace amarlon {

namespace state{

MoveToTarget::MoveToTarget()
{
}

FSMStateType MoveToTarget::getType() const
{
  return FSMStateType::MOVE_TO_TARGET;
}

int MoveToTarget::update(Ai *ai)
{
  if ( ai )
  {
    ActorPtr enemy = ai->getTarget().firstActor();
    ActorPtr me = ai->getOwner().lock();
    MapPtr map = me ? me->getMap() : nullptr;

    if ( me && enemy && map )
    {
      int dx = enemy->getX() - me->getX();
      int dy = enemy->getY() - me->getY();
      int stepDx = (dx > 0 ? 1:-1);
      int stepDy = (dy > 0 ? 1:-1);

      float distance = sqrtf(dx*dx + dy*dy);

      if ( distance > 0 )
      {
        dx = (int)(round(dx/distance));
        dy = (int)(round(dy/distance));

        if ( !map->isBlocked( me->getX()+dx, me->getY()+dy) )
        {
          me->performAction( std::make_shared<MonsterMoveAction>(dx, dy) );
        }
        else if ( !map->isBlocked( me->getX()+stepDx, me->getY()) )
        {
          me->performAction( std::make_shared<MonsterMoveAction>(stepDx, 0) );
        }
        else if ( !map->isBlocked(me->getX(), me->getY()+stepDy) )
        {
          me->performAction( std::make_shared<MonsterMoveAction>(0, stepDy) );
        }
      }
    }
  }
  return 0;
}

}}

