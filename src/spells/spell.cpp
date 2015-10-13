#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <animation.h>
#include <engine.h>
#include <spell_db.h>
#include <lua_state.h>
#include <spell_book.h>

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
  return id != SpellId::Null ? SpellPtr( new Spell(id) ) : nullptr;
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

  //Set spell prepared = false in caster's spellbook
  if ( success )
  {
    CharacterPtr character = caster->getFeature<Character>();
    if ( character && character->getSpellBook() )
    {
      auto sSlots = character->
                    getSpellBook()->
                    getSlots([&](SpellSlotPtr s)
                      { return s->spell && s->spell->getId() == _id; });

      if ( !sSlots.empty() )
      {
        sSlots.front()->isPrepared = false;
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

std::string Spell::getDescription() const
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += Engine::instance().getSpellDB().getDescription(_id) + "# #";

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

}

