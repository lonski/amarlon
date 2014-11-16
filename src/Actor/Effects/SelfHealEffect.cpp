#include "SelfHealEffect.h"
#include <Actor/Actor.h>
#include <utils/messenger.h>
#include "gui/gui.h"

namespace amarlon {

SelfHealEffect::SelfHealEffect()
  : _healAmount(0)
{
}

bool SelfHealEffect::apply(Actor *executor, std::vector<Actor *>)
{
  bool r = false;

  if ( executor->hasFeature<Fighter>() )
  {
    int healed = executor->getFeature<Fighter>()->heal(_healAmount);
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

bool SelfHealEffect::isEqual(Effect *rhs)
{
  bool equal = false;
  SelfHealEffect* crhs = dynamic_cast<SelfHealEffect*>(rhs);

  if (crhs != nullptr)
  {
    equal = _healAmount == crhs->_healAmount;
    equal &= _usesCount == crhs->_usesCount;
  }

  return equal;
}

}
