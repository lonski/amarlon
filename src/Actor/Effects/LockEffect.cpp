#include "LockEffect.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include "Utils/Utils.h"
#include "Utils/DirectionSelector.h"

LockEffect::LockEffect()
{
}

void LockEffect::load(EffectDescription dsc)
{
  _lockId = dsc.lockId;
  _usesCount = dsc.uses;
}

bool LockEffect::apply(Actor*, std::vector<Actor *> targets)
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
          Gui::Root.message("You unlocked the "+tolowers(target->getName())+".");
        }
        r = true;
      }
      else if ( toOpen->getLockId() == _lockId )
      {
        if ( toOpen->lock() )
        {
          Gui::Root.message("You locked the "+tolowers(target->getName())+".");
        }
        r = true;
      }
    }
  }

  return r;
}
