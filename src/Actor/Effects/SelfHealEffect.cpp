#include "SelfHealEffect.h"
#include <Actor/Actor.h>
#include "Utils/Messenger.h"
#include "Gui/Gui.h"

SelfHealEffect::SelfHealEffect()
{
}

bool SelfHealEffect::apply(Actor *executor, std::vector<Actor *>)
{
  bool r = false;

  if ( executor->afFighter() )
  {
    int healed = executor->afFighter()->heal(_healAmount);
    Messenger::message()->actorHealed(executor, healed);

    --_usesCount;
    r = true;
  }

  return r;
}

void SelfHealEffect::load(const EffectDescription &dsc)
{
  _healAmount = dsc.heal;
  _usesCount = dsc.uses;
}

EffectDescription SelfHealEffect::save()
{
  EffectDescription dsc;
  dsc.heal = _healAmount;
  dsc.uses = _usesCount;

  return dsc;
}

Effect *SelfHealEffect::clone()
{
  SelfHealEffect* cloned = new SelfHealEffect;
  cloned->load( save() );

  return cloned;
}
