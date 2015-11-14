#include "range_attack.h"
#include <shot_action.h>
#include <ai.h>
#include <actor.h>

namespace amarlon { namespace state {

RangeAttack::RangeAttack()
{
}

FSMStateType RangeAttack::getType() const
{
  return FSMStateType::ATTACK_RANGE;
}

int RangeAttack::update(Ai *ai)
{
  if ( ai )
  {
    ActorPtr enemy = ai->getTarget().firstActor();
    ActorPtr me = ai->getOwner().lock();

    if ( me && enemy )
    {
      me->performAction( std::make_shared<ShotAction>(enemy) );
    }
  }

  return 0;
}

}}
