#include "move_to_target.h"
#include <ai.h>
#include <map.h>
#include <actor.h>
#include <monster_move_action.h>
#include <utils.h>

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
    if ( me && enemy )
    {
      if ( me->sees(enemy) )
      {
        _path.reset( calculatePath(me, enemy) );
      }
      if ( _path && !_path->isEmpty() )
      {
        int x(0), y(0);
        _path->walk(&x, &y, true);
        me->performAction( new MonsterMoveAction(x - me->getX(), y - me->getY()) );
      }
      else
      {
        ai->setTarget(nullptr);
      }
    }
  }
  return 0;
}

}}

