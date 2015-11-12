#include "melee_attack.h"
#include <attack_action.h>
#include <ai.h>
#include <actor.h>

namespace amarlon { namespace state {

MeleeAttack::MeleeAttack()
{
}

FSMStateType MeleeAttack::getType() const
{
  return FSMStateType::MELEE_ATTACK;
}

int MeleeAttack::update(Ai *ai)
{
  if ( ai )
  {
    ActorPtr enemy = ai->getTarget().firstActor();
    ActorPtr me = ai->getOwner().lock();

    if ( me && enemy )
    {
      me->performAction( std::make_shared<AttackAction>(enemy) );
    }
  }

  return 0;
}

}}
