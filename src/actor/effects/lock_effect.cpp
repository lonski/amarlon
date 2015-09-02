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

Effect *LockEffect::clone()
{
  LockEffect* cloned = new LockEffect;
  cloned->load( save() );

  return cloned;
}

bool LockEffect::isEqual(Effect *rhs)
{
  bool equal = false;
  LockEffect* crhs = dynamic_cast<LockEffect*>(rhs);

  if (crhs != nullptr)
  {
    equal = _lockId == crhs->_lockId;    
  }

  return equal;
}

void LockEffect::load(const EffectDescription &dsc)
{
  _lockId = dsc.lockId;
}

EffectDescription LockEffect::save()
{
  EffectDescription dsc;
  dsc.lockId = _lockId;

  return dsc;
}

EffectType LockEffect::getType() const
{
  return EffectType::Lock;
}

int LockEffect::getLockId() const
{
  return _lockId;
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
