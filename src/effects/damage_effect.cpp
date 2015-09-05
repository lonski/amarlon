#include "damage_effect.h"
#include <utils.h>
#include <actor.h>
#include <character.h>
#include <messenger.h>

namespace amarlon {

DamageEffect::DamageEffect()
  : _damage(0)
  , _type(DamageType::Physical)
{
}

bool DamageEffect::apply(ActorPtr executor, const Target& target)
{
  bool r = false;

  std::function<bool(ActorPtr)> filter = [](ActorPtr a)->bool{ return a->isAlive(); };
  ActorPtr targetActor = target.firstActor(&filter);
  if ( targetActor )
  {
    CharacterPtr character = targetActor->getFeature<Character>();
    if ( character )
    {
      int hpBefore = character->getHitPoints();
      character->takeDamage(_damage, _type);

      Messenger::message()->actorHit(executor, targetActor, hpBefore - character->getHitPoints() );

      r = true;
    }
  }

  return r;
}

void DamageEffect::load(const Params& params)
{
  auto it = params.find("damage");
  _damage = it != params.end() ? fromStr<int>( it->second ) : 0;

  it = params.find("damageType");
  _type = it != params.end() ? static_cast<DamageType>(fromStr<int>( it->second )) : DamageType::Physical;
}

EffectPtr DamageEffect::clone()
{
  EffectPtr cloned( new DamageEffect );
  cloned->load( toParams() );

  return cloned;
}

bool DamageEffect::isEqual(EffectPtr rhs)
{
  bool equal = false;
  DamageEffectPtr crhs = std::dynamic_pointer_cast<DamageEffect>(rhs);

  if (crhs != nullptr)
  {
    equal  = _damage == crhs->_damage;
    equal &= _type   == crhs->_type;
  }

  return equal;
}

EffectType DamageEffect::getType() const
{
  return EffectType::Damage;
}

Params DamageEffect::toParams() const
{
  return {
    {"damage", std::to_string(_damage)},
    {"damageType", std::to_string(static_cast<int>(_type))}
  };
}

}
