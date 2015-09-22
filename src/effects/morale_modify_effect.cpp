#include "morale_modify_effect.h"
#include <actor.h>
#include <monster.h>
#include <status_effects_manager.h>

namespace amarlon {

MoraleModifyEffect::MoraleModifyEffect()
  : _time(0)
  , _modifier(0)
{
}

EffectPtr MoraleModifyEffect::clone()
{
  EffectPtr cloned( new MoraleModifyEffect );
  cloned->load( toParams() );

  return cloned;
}

bool MoraleModifyEffect::isEqual(EffectPtr rhs)
{
  bool equal = false;
  MoraleModifyEffectPtr crhs = std::dynamic_pointer_cast<MoraleModifyEffect>(rhs);

  if (crhs != nullptr)
  {
    equal = _time == crhs->_time;
    equal &= _modifier == crhs->_modifier;
  }

  return equal;
}

bool MoraleModifyEffect::apply(ActorPtr, const Target &target)
{
  bool r = false;
  ActorPtr t = target.firstActor();
  if ( t )
  {
    MonsterPtr m = std::dynamic_pointer_cast<Monster>( t->getFeature<Character>() );
    if ( m )
    {
      m->setTmpMoraleModifier( m->getTmpMoraleModifier() + _modifier );
      t->getStatusEffects().add( shared_from_this() );
      r = true;
    }
  }
  return r;
}

bool MoraleModifyEffect::revoke(ActorPtr, const Target &target)
{
  bool r = false;
  ActorPtr t = target.firstActor();
  if ( t )
  {
    MonsterPtr m = std::dynamic_pointer_cast<Monster>( t->getFeature<Character>() );
    if ( m )
    {
      m->setTmpMoraleModifier( m->getTmpMoraleModifier() - _modifier );
      t->getStatusEffects().add( shared_from_this() );
      r = true;
    }
  }
  return r;
}

EffectType MoraleModifyEffect::getType() const
{
  return EffectType::Morale;
}

void MoraleModifyEffect::load(const Params &params)
{
  auto it = params.find("time");
  _time = it != params.end() ? fromStr<int>( it->second ) : -1;

  it = params.find("modifier");
  _modifier = it != params.end() ? fromStr<int>( it->second ) : 0;
}

Params MoraleModifyEffect::toParams() const
{
  return {
    { {"time", toStr(_time)},
      {"modifier", toStr(_modifier)} }
  };
}

int MoraleModifyEffect::getTime() const
{
  return _time;
}

void MoraleModifyEffect::setTime(int time)
{
  _time = time;
}

}

