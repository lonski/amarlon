#include "heal_effect.h"
#include <actor.h>
#include <gui.h>
#include <messenger.h>
#include <executor_selector.h>
#include <utils.h>

namespace amarlon {

HealEffect::HealEffect()
  : _healAmount(0)
{
}

bool HealEffect::apply(ActorPtr, const Target& target)
{
  bool r = false;

  std::function<bool(ActorPtr)> filter = [](ActorPtr a)->bool{ return a->isAlive(); };
  ActorPtr targetActor = target.firstActor(&filter);
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

void HealEffect::load(const Params& params)
{
  auto it = params.find("heal");
  _healAmount = it != params.end() ? fromStr<int>( it->second ) : 0;
}

EffectPtr HealEffect::clone()
{
  EffectPtr cloned( new HealEffect );
  cloned->load( toParams() );

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
  return EffectType::Heal;
}

int HealEffect::getHealAmount() const
{
  return _healAmount;
}

Params HealEffect::toParams() const
{
  return {
    { {"heal", std::to_string(_healAmount)} }
  };
}

}
