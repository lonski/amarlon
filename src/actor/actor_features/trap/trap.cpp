#include "trap.h"
#include <trap_description.h>
#include <engine.h>
#include <lua_state.h>
#include <actor.h>

namespace amarlon {

const ActorFeature::Type Trap::featureType = ActorFeature::TRAP;

Trap::Trap()
  : _id(TrapId::Null)
  , _armed(false)
  , _difficulty(0)
{
}

Trap::~Trap()
{
}

TrapPtr Trap::create(DescriptionPtr dsc)
{
  TrapPtr trap;
  TrapDescriptionPtr tDsc = std::dynamic_pointer_cast<TrapDescription>(dsc);
  if ( tDsc )
  {
    trap.reset(new Trap);
    trap->_armed = tDsc->armed;
    trap->_difficulty = tDsc->difficulty;
    trap->_id = static_cast<TrapId>(tDsc->id);
    trap->_detected = tDsc->detected;
  }
  return trap;
}

ActorFeature::Type Trap::getType()
{
  return ActorFeature::TRAP;
}

ActorFeaturePtr Trap::clone()
{
  return TrapPtr(new Trap(*this));
}

bool Trap::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;

  TrapPtr tRhs = std::dynamic_pointer_cast<Trap>(rhs);
  if ( tRhs )
  {
    equal =  _armed == tRhs->_armed;
    equal &= _difficulty == tRhs->_difficulty;
    equal &= _id == tRhs->_id;
    equal &= _detected == tRhs->_detected;
  }

  return equal;
}

bool Trap::trigger(Target victim)
{
  bool r = false;

  if ( isArmed() && victim )
  { 
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( getScript() ) )
    {
      try
      {
        for (auto a : victim.actors)
          a->notify( Event(EventId::Actor_TriggeredTrap,
                           { {"trap",getName()} }) );

        r = luabind::call_function<bool>(
            lua()
          , "onTrigger"
          , &victim
          , this
        );

        if ( !r )
        {
          for (auto a : victim.actors)
            a->notify( Event(EventId::Actor_DodgedTrap,
                             { {"trap",getName()} }) );
        }
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }

    setArmed(false);
  }


  return r;
}

bool Trap::isArmed() const
{
  return _armed;
}

void Trap::setArmed(bool armed)
{
  _armed = armed;
}

bool Trap::isDetected() const
{
  return _detected;
}

void Trap::setDetected(bool detected)
{
  _detected = detected;
}

std::string Trap::getScript() const
{
  return "scripts/traps/" + std::to_string( static_cast<int>(_id) ) + ".lua";
}

std::string Trap::getName() const
{
  return TrapId2Str(_id);
}

int Trap::getDifficulty()
{
  return _difficulty;
}

TrapId Trap::getId() const
{
  return _id;
}

}
