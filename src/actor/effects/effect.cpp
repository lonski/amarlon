#include "effect.h"
#include <lock_effect.h>
#include <heal_effect.h>
#include <target_selector.h>
#include <cassert>

namespace amarlon {

Effect::Effect()
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
    case EffectType::SelfHeal: e = new HealEffect; break;
    default:;
  }

  return e;
}

Effect* Effect::create(const EffectDescription &dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  Effect* e = Effect::create(dsc.type);

  if ( e != nullptr )
  {
    e->load(dsc);
  }

  return e;
}

}
