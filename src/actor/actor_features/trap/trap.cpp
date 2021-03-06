#include "trap.h"
#include <trap_description.h>
#include <engine.h>
#include <lua_state.h>
#include <actor.h>
#include <module.h>

namespace amarlon {

const ActorFeature::Type Trap::featureType = ActorFeature::TRAP;

Trap::Trap(DescriptionPtr dsc)
  : _id(TrapId::Null)
  , _armed(false)
  , _difficulty(0)
  , _detected(false)
{
  upgrade(dsc);
}

Trap::~Trap()
{
}

TrapPtr Trap::create(DescriptionPtr dsc)
{
  return TrapPtr( new Trap(dsc) );
}

void Trap::upgrade(DescriptionPtr dsc)
{
  TrapDescriptionPtr tDsc = std::dynamic_pointer_cast<TrapDescription>(dsc);
  if ( tDsc )
  {
    if (tDsc->armed)     _armed = *tDsc->armed;
    if (tDsc->difficulty) _difficulty = *tDsc->difficulty;
    if (tDsc->id)         _id = static_cast<TrapId>(*tDsc->id);
    if (tDsc->detected)   _detected = *tDsc->detected;
  }
}

DescriptionPtr Trap::toDescriptionStruct(ActorFeaturePtr cmp)
{
  TrapDescriptionPtr dsc(new TrapDescription);
  TrapPtr cmpT = std::dynamic_pointer_cast<Trap>(cmp);

  if ( cmpT )
  {
    if ( _armed != cmpT->_armed ) dsc->armed = _armed;
    if ( _id != cmpT->_id ) dsc->id = (int)_id;
    if ( _difficulty != cmpT->_difficulty ) dsc->difficulty = _difficulty;
    if ( _detected != cmpT->_detected ) dsc->detected = _detected;
  }
  else
  {
    dsc->armed = _armed;
    dsc->id = (int)_id;
    dsc->difficulty = _difficulty;
    dsc->detected = _detected;
  }

  return dsc;
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
  if ( armed != _armed )
  {
    _armed = armed;
    EventId id = _armed ? EventId::TrapArmed : EventId::TrapDisarmed;
    getOwner().lock()->notify( Event(id, { {"trap",getName()} }) );
  }
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
  std::string default_script = "scripts/traps/" + std::to_string( static_cast<int>(_id) ) + ".lua";
  std::string module_script = Engine::instance().getModule().getPath() + default_script;

  return file_exists(module_script) ? module_script : default_script;
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
