#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <effect.h>
#include <animation.h>
#include <engine.h>
#include <lua_state.h>
#include <actor_wrapper.h>
#include <effect_forge.h>

namespace amarlon {

Spell::Spell()
  : _name("No name")
  , _class(CharacterClass::NoClass)
  , _level(0)
  , _targetType(TargetType::SINGLE_NEIGHBOUR)
  , _range(0)
  , _radius(0)
  , _duration(0)
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
    spell->_radius = dsc->radius;
    spell->_duration = dsc->duration;

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
  cloned->_radius     = _radius;
  cloned->_duration   = _duration;

  return cloned;
}

bool Spell::cast(ActorPtr caster, Target target)
{
  bool success = false;

  if ( target )
  {
    lua_api::LuaState& state = Engine::instance().getLuaState();
    lua_api::ActorWrapper( caster, "caster" );

    if ( state.execute( getScriptPath() ) )
    {

      success = true;

      if ( _animation )
      {
        _animation->setLocation( Target({caster}, caster->getX(), caster->getY() ), target );
        _animation->run(*TCODConsole::root);
      }

      //Apply effects produced in Lua script
      lua_api::EffectForge& forge = state["forge"];
      for ( auto effect : forge.produce() )
      {
        success &= effect->apply(caster, target);
      }
    }

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

int Spell::getRadius() const
{
  return _radius;
}

int Spell::getDuration() const
{
  return _duration;
}

std::string Spell::getScriptPath() const
{
  return "scripts/spells/" + std::to_string( static_cast<int>(_id) ) + ".lua";
}

}
