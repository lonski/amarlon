#include "saving_throw_modify_effect.h"
#include <actor.h>
#include <character.h>
#include <status_effects_manager.h>

namespace amarlon {

SavingThrowModifyEffect::SavingThrowModifyEffect()
  : _time(-1)
  , _modifier(0)
  , _type(SavingThrows::Spells)
{
}

EffectPtr SavingThrowModifyEffect::clone()
{
  EffectPtr cloned( new SavingThrowModifyEffect );
  cloned->load( toParams() );

  return cloned;
}

bool SavingThrowModifyEffect::isEqual(EffectPtr rhs)
{
  bool equal = false;
  SavingThrowModifyEffectPtr crhs = std::dynamic_pointer_cast<SavingThrowModifyEffect>(rhs);

  if (crhs != nullptr)
  {
    equal = _time == crhs->_time;
    equal &= _modifier == crhs->_modifier;
    equal &= _type == crhs->_type;
  }

  return equal;
}

bool SavingThrowModifyEffect::apply(ActorPtr, const Target &target)
{
  bool r = false;
  for( ActorPtr t : target.actors )
  {
    if ( t )
    {
      CharacterPtr c = t->getFeature<Character>();
      if ( c )
      {
        c->setTmpSavingThrowModifier( _type, c->getTmpSavingThrowModifier(_type) + _modifier );
        t->getStatusEffects().add( shared_from_this() );
        r = true;
      }
    }
  }
  return r;
}

bool SavingThrowModifyEffect::revoke(ActorPtr, const Target &target)
{
  bool r = false;
  for( ActorPtr t : target.actors )
  {
    if ( t )
    {
      CharacterPtr c = t->getFeature<Character>();
      if ( c )
      {
        c->setTmpSavingThrowModifier( _type, c->getTmpSavingThrowModifier(_type) - _modifier );
        t->getStatusEffects().add( shared_from_this() );
        r = true;
      }
    }
  }
  return r;
}

EffectType SavingThrowModifyEffect::getType() const
{
  return EffectType::SavingThrow;
}

void SavingThrowModifyEffect::load(const Params &params)
{
  auto it = params.find("time");
  _time = it != params.end() ? fromStr<int>( it->second ) : -1;

  it = params.find("modifier");
  _modifier = it != params.end() ? fromStr<int>( it->second ) : 0;

  it = params.find("throw_type");
  _type = it != params.end() ? static_cast<SavingThrows::Type>(fromStr<int>( it->second ))
                             : SavingThrows::Spells;
}

Params SavingThrowModifyEffect::toParams() const
{
  return {
    { {"time",     toStr(_time)},
      {"modifier", toStr(_modifier)},
      {"throw_type", toStr(static_cast<int>(_type))} }
  };
}

int SavingThrowModifyEffect::getTime() const
{
  return _time;
}

void SavingThrowModifyEffect::setTime(int time)
{
  _time = time;
}

std::string SavingThrowModifyEffect::getName() const
{
  return "Saving Throw Modify";
}

}
