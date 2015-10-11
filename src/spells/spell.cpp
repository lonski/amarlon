#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <animation.h>
#include <engine.h>
#include <spell_db.h>
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
    SpellDB& spellDb = Engine::instance().getSpellDB();

    if ( lua.execute( spellDb.getScriptPath(_id) ) )
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
  return Engine::instance().getSpellDB().getName(_id);
}
CharacterClass Spell::getClass() const
{
  return Engine::instance().getSpellDB().getClass(_id);
}

int Spell::getLevel() const
{
  return Engine::instance().getSpellDB().getLevel(_id);
}

TargetType Spell::getTargetType() const
{
  return Engine::instance().getSpellDB().getTargetType(_id);
}

int Spell::getRange() const
{
  return Engine::instance().getSpellDB().getRange(_id);
}

int Spell::getRadius() const
{
  return Engine::instance().getSpellDB().getRadius(_id);
}

}

