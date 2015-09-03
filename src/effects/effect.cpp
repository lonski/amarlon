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

EffectPtr Effect::create(EffectType type)
{
  EffectPtr e;

  switch(type)
  {
    case EffectType::Lock:     e.reset( new LockEffect ); break;
    case EffectType::SelfHeal: e.reset( new HealEffect ); break;
    default:;
  }

  return e;
}

EffectPtr Effect::create(const EffectDescription &dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  EffectPtr e = Effect::create(dsc.type);

  if ( e != nullptr )
  {
    e->load(dsc);
  }

  return e;
}

}
