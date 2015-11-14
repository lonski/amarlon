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

int MeleeAttack::update()
{
  if ( _ai )
  {
    ActorPtr enemy = _ai->getTarget().firstActor();
    ActorPtr me = _ai->getOwner().lock();

    if ( me && enemy )
    {
      me->performAction( std::make_shared<AttackAction>(enemy) );
    }
  }

  return 0;
}

bool MeleeAttack::canEnter()
{
  return true;
}

}}
