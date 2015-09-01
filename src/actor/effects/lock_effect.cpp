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

TargetType LockEffect::getTargetType() const
{
  return TargetType::SINGLE_NEIGHBOUR;
}

EffectType LockEffect::getType() const
{
  return EffectType::Lock;
}

int LockEffect::getLockId() const
{
  return _lockId;
}

bool LockEffect::apply(ActorPtr executor, std::vector<ActorPtr > targets)
{
  bool r = false;

  if (targets.size() == 1 && targets[0] != nullptr)
  {
    ActorPtr target = targets.front();
    OpenablePtr toOpen = targets.front()->getFeature<Openable>();

    if (toOpen != nullptr)
    {
      if (toOpen->isLocked() && toOpen->getLockId() == _lockId)
      {
        if ( toOpen->unlock() )
        {
          Messenger::message()->actorHasBeenUnLocked(executor, target);
        }
        r = true;
      }
      else if ( toOpen->getLockId() == _lockId )
      {
        if ( toOpen->lock() )
        {
          Messenger::message()->actorHasBeenLocked(executor, target);
        }
        r = true;
      }
    }
  }

  return r;
}

}
