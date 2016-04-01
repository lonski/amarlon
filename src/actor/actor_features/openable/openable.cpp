#include "openable.h"
#include <amarlon_except.h>
#include <actor.h>
#include <lua_state.h>
#include <engine.h>
#include <message_box.h>

namespace amarlon {

const ActorFeature::Type Openable::FeatureType = ActorFeature::OPENABLE;

Openable::Openable(const OpenableData &data)
{
  _data.CopyFrom(data);
}

OpenablePtr Openable::create(const OpenableData &data)
{
  return OpenablePtr( new Openable(data) );
}

Openable::Openable()
{
}

Openable::Openable(const Openable &rhs)
{
  *this = rhs;
}

Openable::~Openable()
{
}

bool Openable::operator==(const Openable &rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Openable& Openable::operator=(const Openable& rhs)
{
  if ( this != &rhs )
  {
    _data.CopyFrom(rhs._data);
  }
  return *this;
}

const OpenableData &Openable::getData() const
{
  return _data;
}

const google::protobuf::Message& Openable::getDataPolymorphic() const
{
  return getData();
}

ActorFeature::Type Openable::getFeatureType()
{
  return FeatureType;
}

bool Openable::open(ActorPtr executor)
{
  bool r = false;
  if ( getScriptId() > 0 && isClosed() )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();

    if ( lua.execute( getScriptPath() ) )
    {
      try
      {
        r = luabind::call_function<bool>(
            lua()
          , "onOpen"
          , executor
          , getOwner().lock()
        );

        _data.set_closed(!r);

        ActorPtr owner = getOwner().lock();
        if ( owner ) owner->interract(executor);
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }
  }

  return r;
}

bool Openable::close(ActorPtr executor)
{
  bool r = false;

  if ( getScriptId() > 0 && !isClosed() )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();

    if ( lua.execute( getScriptPath() ) )
    {
      try
      {
        r = luabind::call_function<bool>(
            lua()
          , "onClose"
          , executor
          , getOwner().lock()
        );

        _data.set_closed(r);

        ActorPtr owner = getOwner().lock();
        if ( owner ) owner->interract(executor);
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }
  }

  return r;
}

bool Openable::isClosed() const
{
  return _data.closed();
}

bool Openable::lock()
{
  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event(EventId::Actor_Locked));
  }
  _data.set_locked(true);
  return true;
}

bool Openable::unlock()
{
  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event(EventId::Actor_Unlocked));
  }
  _data.set_locked(false);
  return true;
}

std::string Openable::getScriptPath() const
{
  return "scripts/openable/" + std::to_string( getScriptId() ) + ".lua";
}

bool Openable::isLocked() const
{
  return _data.locked();
}

int Openable::getLockId() const
{
  return _data.lock_id();
}

int Openable::getLockLevel() const
{
  return _data.lock_level();
}

int Openable::getScriptId() const
{
  return _data.script_id();
}

}

