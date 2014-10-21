#include "LockEffect.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include "Utils/Utils.h"
#include "Utils/DirectionSelector.h"
#include "Utils/Messenger.h"

LockEffect::LockEffect()
{
}

void LockEffect::load(const EffectDescription &dsc)
{
  _lockId = dsc.lockId;
  _usesCount = dsc.uses;
}

bool LockEffect::apply(Actor* executor, std::vector<Actor *> targets)
{
  bool r = false;

  if (targets.size() == 1 && targets[0] != nullptr)
  {
    Actor* target = targets.front();
    Openable* toOpen = targets.front()->afOpenable();

    if (toOpen)
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
