#include "Effect.h"
#include "LockEffect.h"
#include "HealEffect.h"

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
    case EffectType::Heal: e = new HealEffect; break;
  }

  return e;
}

int Effect::getUsesCount() const
{
  return _usesCount;
}
