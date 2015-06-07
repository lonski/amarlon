#include "self_heal_effect.h"
#include "actor/actor.h"
#include "gui/gui.h"
#include "utils/messenger.h"
#include "utils/target_selector/executor_selector.h"

namespace amarlon {

SelfHealEffect::SelfHealEffect()
  : _healAmount(0)
{
}

bool SelfHealEffect::apply(ActorPtr executor, std::vector<ActorPtr >)
{
  bool r = false;

  CharacterPtr character = executor->getFeature<Character>();
  if ( character )
  {    
    int hpBeforeHeal = character->getHitPoints();
    character->modifyHitPoints(_healAmount);

    Messenger::message()->actorHealed(executor, character->getHitPoints() - hpBeforeHeal );

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

void SelfHealEffect::setHealAmount(int amount)
{
  _healAmount = amount;
}

TargetType SelfHealEffect::getTargetType() const
{
  return TargetType::SELF;
}

}
