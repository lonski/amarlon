#include "spell.h"
#include <effect.h>

namespace amarlon {

Spell::Spell()
  : _name("No name")
  , _class(CharacterClass::NoClass)
  , _level(0)
  , _targetType(TargetType::SINGLE_NEIGHBOUR)
{
}

Spell::~Spell()
{
}

SpellPtr Spell::create(SpellDescriptionPtr dsc)
{
  SpellPtr spell;

  if ( dsc )
  {
    spell.reset( new Spell );

    spell->_name = dsc->name;
    spell->_level = dsc->level;
    spell->_class = static_cast<CharacterClass>(dsc->spellClass);
    spell->_targetType = static_cast<TargetType>(dsc->targetType);

    for ( auto& effectDsc : dsc->effects )
    {
      spell->_effects.push_back( Effect::create(effectDsc) );
    }
  }

  return spell;
}

bool Spell::cast(ActorPtr caster, Target target)
{
  bool success = true;

  for ( auto effect : _effects )
  {
    success &= effect->apply(caster, target);
    //TODO : revoke applied effect if any failed
  }

  return success;
}

std::string Spell::getName() const
{
  return _name;
}
CharacterClass Spell::getClass() const
{
  return _class;
}

int Spell::getLevel() const
{
  return _level;
}

TargetType Spell::getTargetType() const
{
  return _targetType;
}

}
