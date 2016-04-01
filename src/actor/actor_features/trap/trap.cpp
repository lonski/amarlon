#include "trap.h"
#include <engine.h>
#include <lua_state.h>
#include <actor.h>

namespace amarlon {

const ActorFeature::Type Trap::FeatureType = ActorFeature::TRAP;

TrapPtr Trap::create(const TrapData &data)
{
  return TrapPtr( new Trap(data) );
}

Trap::Trap()
{
}

Trap::Trap(const TrapData& data)
{
  _data.CopyFrom(data);
}

Trap::Trap(const Trap &rhs)
{
  *this = rhs;
}

Trap::~Trap()
{
}

bool Trap::operator==(const Trap &rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Trap &Trap::operator=(const Trap &rhs)
{
  if ( this != &rhs )
  {
    _data.CopyFrom(rhs._data);
  }
  return *this;
}

const TrapData &Trap::getData() const
{
  return _data;
}

const google::protobuf::Message& Trap::getDataPolymorphic() const
{
  return getData();
}

ActorFeature::Type Trap::getFeatureType()
{
  return FeatureType;
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
  return _data.is_armed();
}

void Trap::setArmed(bool armed)
{
  if ( armed != isArmed() )
  {
    _data.set_is_armed(armed);
    EventId id = isArmed() ? EventId::TrapArmed : EventId::TrapDisarmed;
    getOwner().lock()->notify( Event(id, { {"trap",getName()} }) );
  }
}

bool Trap::isDetected() const
{
  return _data.is_detected();
}

void Trap::setDetected(bool detected)
{
  _data.set_is_detected(detected);
}

std::string Trap::getScript() const
{
  return "scripts/traps/" + std::to_string( static_cast<int>( getId() ) ) + ".lua";
}

std::string Trap::getName() const
{
  return TrapId2Str( getId() );
}

int Trap::getDifficulty()
{
  return _data.difficulty();
}

TrapId Trap::getId() const
{
  return static_cast<TrapId>(_data.id());
}

}
