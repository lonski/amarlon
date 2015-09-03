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

void HealEffect::load(EffectDescriptionPtr dsc)
{
  _healAmount = dsc->heal;
}

EffectDescriptionPtr HealEffect::save()
{
  EffectDescriptionPtr dsc(new EffectDescription );
  dsc->heal = _healAmount;

  return dsc;
}

EffectPtr HealEffect::clone()
{
  EffectPtr cloned( new HealEffect );
  cloned->load( save() );

  return cloned;
}

bool HealEffect::isEqual(EffectPtr rhs)
{
  bool equal = false;
  HealEffectPtr crhs = std::dynamic_pointer_cast<HealEffect>(rhs);

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
