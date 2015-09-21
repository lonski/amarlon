#include "damage_effect.h"
#include <utils.h>
#include <actor.h>
#include <character.h>


namespace amarlon {

DamageEffect::DamageEffect()
{
}

bool DamageEffect::apply(ActorPtr executor, const Target& target)
{
  bool r = false;

  for ( auto a : target.actors )
  {
    CharacterPtr character = a->getFeature<Character>();
    if ( character )
    {
      character->takeDamage(_damage, executor);
      r = true;
    }
  }

  return r;
}

bool DamageEffect::revoke(ActorPtr, const Target&)
{
  return true;
}

void DamageEffect::load(const Params& params)
{
  auto it = params.find("damage");
  _damage = it != params.end() ? Damage( it->second ) : Damage();
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
    equal  =  _damage == crhs->_damage;
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
    {"damage", _damage}
  };
}

}
