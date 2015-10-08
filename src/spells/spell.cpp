#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <animation.h>
#include <engine.h>
#include <spell_database.h>
#include <lua_state.h>

namespace amarlon {

Spell::Spell(SpellId id)
  : _id(id)
{
}

Spell::~Spell()
{
}

SpellPtr Spell::create(SpellId id)
{
  return SpellPtr( new Spell(id) );
}

SpellPtr Spell::clone()
{
  return create(_id);
}

bool Spell::cast(ActorPtr caster, Target target)
{
  bool success = false;

  if ( target )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    SpellDatabase& SpellDatabase = Engine::instance().getSpellDatabase();

    if ( lua.execute( SpellDatabase.getScriptPath(_id) ) )
    {
      try
      {
        success = luabind::call_function<bool>(
            lua()
          , "onCast"
          , caster
          , &target
        );
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
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
  return Engine::instance().getSpellDatabase().getName(_id);
}
CharacterClass Spell::getClass() const
{
  return Engine::instance().getSpellDatabase().getClass(_id);
}

int Spell::getLevel() const
{
  return Engine::instance().getSpellDatabase().getLevel(_id);
}

TargetType Spell::getTargetType() const
{
  return Engine::instance().getSpellDatabase().getTargetType(_id);
}

int Spell::getRange() const
{
  return Engine::instance().getSpellDatabase().getRange(_id);
}

int Spell::getRadius() const
{
  return Engine::instance().getSpellDatabase().getRadius(_id);
}

}

