#include "attack_roll_effect.h"
#include <utils.h>
#include <actor.h>
#include <character.h>
#include <status_effects_manager.h>

namespace amarlon {

AttackRollEffect::AttackRollEffect()
  : _time(-1)
  , _modifier(0)
{
}

EffectPtr AttackRollEffect::clone()
{
  EffectPtr cloned( new AttackRollEffect );
  cloned->load( toParams() );

  return cloned;
}

bool AttackRollEffect::isEqual(EffectPtr rhs)
{
  bool equal = false;
  AttackRollEffectPtr crhs = std::dynamic_pointer_cast<AttackRollEffect>(rhs);

  if (crhs != nullptr)
  {
    equal = _time == crhs->_time;
    equal &= _modifier = crhs->_modifier;
  }

  return equal;
}

bool AttackRollEffect::apply(ActorPtr, const Target &target)
{
  bool r = false;
  ActorPtr t = target.firstActor();
  if ( t )
  {
    CharacterPtr c = t->getFeature<Character>();
    if ( c )
    {
      c->setExtraAttackBonus( c->getExtraAttackBonus() + _modifier );
      t->getStatusEffects().add( shared_from_this() );
      r = true;
    }
  }
  return r;
}

bool AttackRollEffect::revoke(ActorPtr, const Target &target)
{
  bool r = false;
  ActorPtr t = target.firstActor();
  if ( t )
  {
    CharacterPtr c = t->getFeature<Character>();
    if ( c )
    {
      c->setExtraAttackBonus( c->getExtraAttackBonus() - _modifier );
      r = true;
    }
  }
  return r;
}

EffectType AttackRollEffect::getType() const
{
  return EffectType::AttackRoll;
}

void AttackRollEffect::load(const Params &params)
{
  auto it = params.find("time");
  _time = it != params.end() ? fromStr<int>( it->second ) : -1;

  it = params.find("modifier");
  _modifier = it != params.end() ? fromStr<int>( it->second ) : 0;
}

Params AttackRollEffect::toParams() const
{
  return {
    { {"time", toStr(_time)},
      {"modifier", toStr(_modifier)} }
  };
}

int AttackRollEffect::getTime() const
{
  return _time;
}

void AttackRollEffect::setTime(int time)
{
  _time = time;
}

}

