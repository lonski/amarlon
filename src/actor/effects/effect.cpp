#include "effect.h"
#include "lock_effect.h"
#include "self_heal_effect.h"
#include <amarlon_except.h>
#include <utils/target_selector/target_selector.h>

namespace amarlon {

Effect::Effect()
  : _usesCount(0)
{
}

Effect::~Effect()
{
}

Effect *Effect::create(EffectType type)
{
  Effect* e = nullptr;

  switch(type)
  {
    case EffectType::Lock: e = new LockEffect; break;
    case EffectType::SelfHeal: e = new SelfHealEffect; break;
    default:;
  }

  return e;
}

Effect *Effect::create(const EffectDescription &dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  Effect* e = Effect::create(dsc.type);

  if ( e != nullptr )
  {
    e->load(dsc);
  }

  return e;
}

TargetSelector& Effect::getTargetSelector()
{
  if ( !_targetSelector ) throw amarlon_exeption("Target selector not set in effect!");
  return *_targetSelector.get();
}

int Effect::getUsesCount() const
{
  return _usesCount;
}

}
