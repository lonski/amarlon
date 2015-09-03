#include "heal_effect.h"
#include <actor.h>
#include <gui.h>
#include <messenger.h>
#include <executor_selector.h>

namespace amarlon {

HealEffect::HealEffect()
  : _healAmount(0)
{
}

bool HealEffect::apply(ActorPtr, const Target& target)
{
  bool r = false;

  ActorPtr targetActor = target.firstActor();
  if ( targetActor )
  {
    CharacterPtr character = targetActor->getFeature<Character>();
    if ( character )
    {
      int hpBeforeHeal = character->getHitPoints();
      character->modifyHitPoints(_healAmount);

      Messenger::message()->actorHealed(targetActor, character->getHitPoints() - hpBeforeHeal );

      r = true;
    }
  }
  return r;
}

void HealEffect::load(const EffectDescription &dsc)
{
  _healAmount = dsc.heal;
}

EffectDescription HealEffect::save()
{
  EffectDescription dsc;
  dsc.heal = _healAmount;

  return dsc;
}

Effect *HealEffect::clone()
{
  HealEffect* cloned = new HealEffect;
  cloned->load( save() );

  return cloned;
}

bool HealEffect::isEqual(Effect *rhs)
{
  bool equal = false;
  HealEffect* crhs = dynamic_cast<HealEffect*>(rhs);

  if (crhs != nullptr)
  {
    equal = _healAmount == crhs->_healAmount;
  }

  return equal;
}

void HealEffect::setHealAmount(int amount)
{
  _healAmount = amount;
}

EffectType HealEffect::getType() const
{
  return EffectType::SelfHeal;
}

int HealEffect::getHealAmount() const
{
  return _healAmount;
}

}
