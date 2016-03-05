#include "spell.h"
#include <libtcod.h>
#include <actor.h>
#include <animation.h>
#include <engine.h>
#include <lua_state.h>
#include <spell_book.h>
#include <spell_db.h>
#include <google/protobuf/util/message_differencer.h>

namespace amarlon {

Spell::Spell(const SpellData* data)
  : _data(data)
{
}

SpellPtr Spell::create(SpellId id)
{
  return Engine::instance().getSpellDB().fetch(id);
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
                             s->spell->getId() == getId();
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
  return _data ? static_cast<SpellId>(_data->id()) : SpellId::Null;
}

std::string Spell::getName() const
{
  return _data ? _data->name() : "No name";
}

CharacterClassType Spell::getClass() const
{
  return _data ? static_cast<CharacterClassType>(_data->char_class())
                    : CharacterClassType::NoClass;
}

int Spell::getLevel() const
{
  return _data ? _data->level() : 0;
}

TargetType Spell::getTargetType() const
{
  return _data ? static_cast<TargetType>(_data->target_type())
                    : TargetType::SELF;
}

int Spell::getRange() const
{
  return _data ? _data->range() : 0;
}

int Spell::getRadius() const
{
  return _data ? _data->radius() : 0;
}

std::string Spell::getDescription() const
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += _data ? _data->description() : "";

  str += colorToStr(TCODColor::darkTurquoise, true) + "Class : " + CharacterClass2Str( getClass() ) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Level : " + toStr(getLevel()) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Range : " + toStr(getRange()) + "#";
  str += colorToStr(TCODColor::darkTurquoise, true) + "Radius: " + toStr(getRadius()) + "#";

  return str;
}

bool Spell::operator==(const Spell &rhs)
{  
  if ( _data != nullptr && rhs._data != nullptr )
    return google::protobuf::util::MessageDifferencer::Equals(*_data, *rhs._data);

  return _data == rhs._data;
}

std::string Spell::getScript() const
{
  return _data ? "scripts/spells/" + std::to_string( static_cast<int>(_data->id()) ) + ".lua" : "";
}

bool Spell::isInitialized() const
{
  return _data != nullptr;
}

}

