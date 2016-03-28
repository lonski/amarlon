#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <animation.h>
#include <engine.h>
#include <lua_state.h>
#include <spell_book.h>
#include <spell_db.h>


namespace amarlon {

Spell::Spell(const SpellData& data)
{
  _data.CopyFrom(data);
}

Spell::Spell(const Spell& spell)
{
  *this = spell;
}

SpellPtr Spell::create(SpellId id)
{
  return Engine::instance().getSpellDB().fetch(id);
}

SpellPtr Spell::clone() const
{
  return SpellPtr(new Spell(*this));
}

Spell& Spell::operator=(const Spell& spell)
{
  if ( this != &spell )  _data.CopyFrom(spell._data);
  return *this;
}

bool Spell::operator==(const Spell &rhs)
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Spell::~Spell()
{
}

bool Spell::cast(ActorPtr caster, Target target)
{
  bool success = false;

  if ( target )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( getScript() ) )
    {
      try
      {
        success = luabind::call_function<bool>(
            lua()
          , "onCast"
          , caster
          , &target
          , this
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
                    getSlots([&](SpellSlotPtr s){
                      return s->spell &&
                             s->isPrepared &&
                             *s->spell == *this;
                    });

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
  return static_cast<SpellId>(_data.id());
}

std::string Spell::getName() const
{
  return _data.name();
}

CharacterClassType Spell::getClass() const
{
  return static_cast<CharacterClassType>(_data.char_class());
}

int Spell::getLevel() const
{
  return _data.level();
}

TargetType Spell::getTargetType() const
{
  return static_cast<TargetType>(_data.target_type());
}

int Spell::getRange() const
{
  return _data.range();
}

int Spell::getRadius() const
{
  return _data.radius();
}

std::string Spell::getDescription() const
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += _data.description();

  str += colorToStr(TCODColor::darkTurquoise, true) + "Class : " + CharacterClass2Str( getClass() ) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Level : " + toStr(getLevel()) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Range : " + toStr(getRange()) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Radius: " + toStr(getRadius()) + "#";

  return str;
}

std::string Spell::getScript() const
{
  return "scripts/spells/" + std::to_string( static_cast<int>(_data.id()) ) + ".lua";
}

}

