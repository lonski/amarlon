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
  return Engine::instance().getSpellDB().fetch(id);
}

SpellPtr Spell::clone()
{
  SpellPtr s(new Spell(_id));
  s->_flyweight = _flyweight;
  return s;
}

CastResult Spell::cast(ActorPtr caster, Target target)
{
  CastResult r = CastResult::Nok;

  if ( target )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( getScript() ) )
    {
      try
      {
        int code = luabind::call_function<int>(
            lua()
          , "onCast"
          , caster
          , &target
          , this
        );

        r = static_cast<CastResult>(code);
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }
  }

  return r;
}

SpellId Spell::getId() const
{
  return _id;
}

std::string Spell::getName() const
{
  return _flyweight ? _flyweight->name : "No name";
}

CharacterClassType Spell::getClass() const
{
  return _flyweight ? static_cast<CharacterClassType>(_flyweight->spellClass)
                    : CharacterClassType::NoClass;
}

int Spell::getLevel() const
{
  return _flyweight ? _flyweight->level : 0;
}

TargetType Spell::getTargetType() const
{
  return _flyweight ? static_cast<TargetType>(_flyweight->targetType)
                    : TargetType::SELF;
}

int Spell::getRange() const
{
  return _flyweight ? _flyweight->range : 0;
}

int Spell::getRadius() const
{
  return _flyweight ? _flyweight->radius : 0;
}

std::string Spell::getDescription() const
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += _flyweight ? _flyweight->description : "";

  str += colorToStr(TCODColor::darkTurquoise, true) + "Class : " + CharacterClass2Str( getClass() ) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Level : " + toStr(getLevel()) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Range : " + toStr(getRange()) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Radius: " + toStr(getRadius()) + "#";

  return str;
}

bool Spell::operator==(const Spell &rhs)
{
  return _id == rhs._id;
}

std::string Spell::getScript() const
{
  return Engine::instance().getSpellDB().getScript(_id);
}

}

