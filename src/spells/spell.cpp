#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <effect.h>
#include <animation.h>

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

    spell->_animation = animation::Animation::create( dsc->animation  );
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
  cloned->_animation  = _animation->clone();

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
  if ( _animation )
  {
    _animation->setLocation( Target({caster}, caster->getX(), caster->getY() ), target );
    _animation->run(*TCODConsole::root);
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
