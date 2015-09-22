#include "heal_effect.h"
#include <actor.h>
#include <gui.h>

#include <executor_selector.h>
#include <utils.h>

namespace amarlon {

HealEffect::HealEffect()
{
}

bool HealEffect::apply(ActorPtr, const Target& target)
{
  bool r = false;

  std::function<bool(ActorPtr)> filter = [](ActorPtr a)->bool{ return a->isAlive(); };
  for ( ActorPtr a : target.actors )
  {
    if ( a && filter(a) )
    {
      CharacterPtr character = a->getFeature<Character>();
      if ( character )
      {
        int hpBeforeHeal = character->getHitPoints();
        character->modifyHitPoints( _heal.roll() );
        a->notify(Event(EventId::Actor_Healed,
                                  {{"value", std::to_string(character->getHitPoints() - hpBeforeHeal) }}));

        r = true;
      }
    }
  }
  return r;
}

bool HealEffect::revoke(ActorPtr, const Target&)
{
  return true;
}

void HealEffect::load(const Params& params)
{
  auto it = params.find("heal");
  _heal = it != params.end() ? Damage( it->second ) : Damage();
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
    equal = _heal == crhs->_heal;
  }

  return equal;
}

EffectType HealEffect::getType() const
{
  return EffectType::Heal;
}

Params HealEffect::toParams() const
{
  return {
    { {"heal", _heal} }
  };
}

std::string HealEffect::getName() const
{
  return "Heal";
}

}

