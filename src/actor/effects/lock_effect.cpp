#include "lock_effect.h"
#include "actor/actor.h"
#include "gui/gui.h"
#include "utils/utils.h"
#include "utils/target_selector/single_neighbour_selector.h"
#include "utils/messenger.h"
#include "gui/message_box.h"

namespace amarlon {

LockEffect::LockEffect()
  : _lockId(0)
{
  _targetSelector.reset( new SingleNeighbourSelector );
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
