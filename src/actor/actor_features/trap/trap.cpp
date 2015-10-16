#include "trap.h"
#include <trap_description.h>
#include <spell.h>

namespace amarlon {

Trap::Trap()
  : _armed(false)
  , _difficulty(0)
{
}

Trap::~Trap()
{
}

TrapPtr Trap::create(DescriptionPtr dsc)
{
  TrapPtr trap;
  TrapDescriptionPtr tDsc = std::dynamic_pointer_cast<TrapDescription>(dsc);
  if ( tDsc )
  {
    trap->_armed = tDsc->armed;
    trap->_spell = Spell::create( static_cast<SpellId>(tDsc->spell) );
  }
  return trap;
}

ActorFeature::Type Trap::getType()
{
  return ActorFeature::TRAP;
}

ActorFeaturePtr Trap::clone()
{
  TrapPtr trap( new Trap );

  trap->_armed = _armed;
  trap->_spell = _spell->clone();

  return trap;
}

bool Trap::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;

  TrapPtr tRhs = std::dynamic_pointer_cast<Trap>(rhs);
  if ( tRhs )
  {
    equal = _armed == tRhs->_armed;
    equal &= *_spell == *tRhs->_spell;
  }

  return equal;
}

void Trap::trigger(Target victim)
{
  if ( isArmed() && _spell )
  {
    _spell->cast( getOwner().lock(), victim );
  }
}

bool Trap::isArmed() const
{
  return _armed;
}

void Trap::setArmed(bool armed)
{
  _armed = armed;
}

int Trap::getDifficulty()
{
  return _difficulty;
}

SpellId Trap::getSpellId() const
{
  return _spell ? _spell->getId() : SpellId::Null;
}

}
