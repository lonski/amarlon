#include "LockEffect.h"
#include "Actor/Actor.h"
#include "gui/gui.h"
#include "utils/utils.h"
#include "utils/direction_selector.h"
#include "utils/messenger.h"

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
    equal &= _usesCount == crhs->_usesCount;
  }

  return equal;
}

void LockEffect::load(const EffectDescription &dsc)
{
  _lockId = dsc.lockId;
  _usesCount = dsc.uses;
}

EffectDescription LockEffect::save()
{
  EffectDescription dsc;
  dsc.lockId = _lockId;
  dsc.uses = _usesCount;

  return dsc;
}

bool LockEffect::apply(Actor* executor, std::vector<Actor *> targets)
{
  bool r = false;

  if (targets.size() == 1 && targets[0] != nullptr)
  {
    Actor* target = targets.front();
    Openable* toOpen = targets.front()->getFeature<Openable>();

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
