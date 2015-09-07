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
  , _range(0)
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
    spell->_range = dsc->range;

    for ( auto& pair : dsc->effects )
    {
      std::vector<EffectPtr> effects;
      for ( auto effectDsc : pair.second )
      {
        effects.push_back( Effect::create(effectDsc) );
      }

      spell->_effects.insert( std::make_pair(pair.first, effects) );
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
  cloned->_range      = _range;

  for ( auto& pair : _effects )
  {
    std::vector<EffectPtr> clonedEffects;
    for( auto e : pair.second )
    {
      clonedEffects.push_back( e->clone() );
    }
    cloned->_effects.insert( std::make_pair(pair.first, clonedEffects) );
  }

  return cloned;
}

bool Spell::cast(ActorPtr caster, Target target)
{
  bool success = true;

  if ( _animation )
  {
    _animation->setLocation( Target({caster}, caster->getX(), caster->getY() ), target );
    _animation->run(*TCODConsole::root);
  }

  for ( auto effect : getEffectsFor( caster ) )
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

int Spell::getRange() const
{
  return _range;
}

std::vector<EffectPtr> Spell::getEffectsFor(ActorPtr actor)
{
  CharacterPtr character = actor->getFeature<Character>();
  if ( character )
  {
    for(auto it = _effects.rbegin(); it != _effects.rend(); ++it )
    {
     if ( it->first <= character->getLevel() ) return it->second;
    }
  }
  return std::vector<EffectPtr>{};
}

}
