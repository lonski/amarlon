#include "lock_effect.h"
#include <actor.h>
#include <gui.h>
#include <utils.h>
#include <messenger.h>

namespace amarlon {

LockEffect::LockEffect()
  : _lockId(0)
{
}

EffectPtr LockEffect::clone()
{
  EffectPtr cloned( new LockEffect );
  cloned->load( toParams() );

  return cloned;
}

bool LockEffect::isEqual(EffectPtr rhs)
{
  bool equal = false;
  LockEffectPtr crhs = std::dynamic_pointer_cast<LockEffect>(rhs);

  if (crhs != nullptr)
  {
    equal = _lockId == crhs->_lockId;    
  }

  return equal;
}

void LockEffect::load(const Params &params)
{
  auto it = params.find("lock");
  _lockId = it != params.end() ? fromStr<int>( it->second ) : 0;
}

EffectType LockEffect::getType() const
{
  return EffectType::Lock;
}

int LockEffect::getLockId() const
{
  return _lockId;
}

Params LockEffect::toParams() const
{
  return {
    { {"lock", std::to_string(_lockId)} }
  };
}

bool LockEffect::apply(ActorPtr executor, const Target& target)
{
  bool r = false;

  ActorPtr targetActor = target.firstActor();
  if (targetActor != nullptr)
  {
    OpenablePtr toOpen = targetActor->getFeature<Openable>();

    if (toOpen != nullptr)
    {
      if (toOpen->isLocked() && toOpen->getLockId() == _lockId)
      {
        if ( toOpen->unlock() )
        {
          Messenger::message()->actorHasBeenUnLocked(executor, targetActor);
        }
        r = true;
      }
      else if ( toOpen->getLockId() == _lockId )
      {
        if ( toOpen->lock() )
        {
          Messenger::message()->actorHasBeenLocked(executor, targetActor);
        }
        r = true;
      }
    }
  }

  return r;
}

}
