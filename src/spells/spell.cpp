#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <animation.h>
#include <engine.h>
#include <spell_database.h>
#include <lua_state.h>
#include <spells.pb.h>

namespace amarlon {

Spell::Spell(SpellId id, proto::SpellData* flyweight)
  : _id(id)
  , _flyweight(flyweight)
{
}

Spell::~Spell()
{
}

SpellPtr Spell::create(SpellId id, proto::SpellData *flyweight)
{
  return SpellPtr( new Spell(id, flyweight) );
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
  return _flyweight ? _flyweight->name()
                    : Engine::instance().getSpellDatabase().getName(_id);
}
CharacterClass Spell::getClass() const
{
  return _flyweight ? static_cast<CharacterClass>(_flyweight->class_())
                    : Engine::instance().getSpellDatabase().getClass(_id);
}

int Spell::getLevel() const
{
  return _flyweight ? _flyweight->level()
                    : Engine::instance().getSpellDatabase().getLevel(_id);
}

TargetType Spell::getTargetType() const
{
  return _flyweight ? static_cast<TargetType>(_flyweight->target())
                    : Engine::instance().getSpellDatabase().getTargetType(_id);
}

int Spell::getRange() const
{
  return _flyweight ? _flyweight->range()
                    : Engine::instance().getSpellDatabase().getRange(_id);
}

int Spell::getRadius() const
{
  return _flyweight ? _flyweight->radius()
                    : Engine::instance().getSpellDatabase().getRadius(_id);
}

}

