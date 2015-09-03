#include "spell.h"
#include <effect.h>

namespace amarlon {

SpellGateway Spell::Gateway;

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
    spell->_id = static_cast<SpellId>(dsc->id);

    for ( auto& effectDsc : dsc->effects )
    {
      spell->_effects.push_back( Effect::create(effectDsc) );
    }
  }

  return spell;
}

SpellPtr Spell::clone()
{
  SpellPtr cloned = std::make_shared<Spell>();

  cloned->_name       = _name;
  cloned->_class      = _class;
  cloned->_level      = _level;
  cloned->_targetType = _targetType;
  cloned->_id         = _id;

  for ( auto e : _effects )
  {
    cloned->_effects.push_back( e->clone() );
  }

  return cloned;
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

SpellId Spell::getId() const
{
  return _id;
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
