#include "Effect.h"
#include "LockEffect.h"
#include "SelfHealEffect.h"

namespace amarlon {

Effect::Effect()
  : _usesCount(0)
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

int Effect::getUsesCount() const
{
  return _usesCount;
}

}
