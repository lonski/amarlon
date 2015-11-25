#include "openable.h"
#include <amarlon_except.h>
#include <actor_descriptions.h>
#include <actor.h>
#include <lua_state.h>
#include <engine.h>
#include <message_box.h>

namespace amarlon {

const ActorFeature::Type Openable::featureType = ActorFeature::OPENABLE;

Openable::Openable(DescriptionPtr dsc)
  : _locked(false)
  , _lockId(0)
  , _lockLevel(0)
  , _scriptId(0)
  , _closed(false)
{
  upgrade(dsc);
}

void Openable::upgrade(DescriptionPtr dsc)
{
  OpenableDescriptionPtr oDsc = std::dynamic_pointer_cast<OpenableDescription>(dsc);
  if ( oDsc )
  {
    if ( oDsc->lockId )    _lockId    = *oDsc->lockId;
    if ( oDsc->lockLevel ) _lockLevel = *oDsc->lockLevel;
    if ( oDsc->locked )    _locked    = *oDsc->locked;
    if ( oDsc->scriptId )  _scriptId  = *oDsc->scriptId;
    if ( oDsc->closed )    _closed    = *oDsc->closed;
  }
}

DescriptionPtr Openable::toDescriptionStruct(ActorFeaturePtr cmp)
{
  OpenableDescriptionPtr dsc(new OpenableDescription);
  OpenablePtr cmpO = std::dynamic_pointer_cast<Openable>(cmp);

  if ( cmpO )
  {
    if ( _lockId != cmpO->_lockId )       dsc->lockId = _lockId;
    if ( _locked != cmpO->_locked )       dsc->locked = _locked;
    if ( _scriptId != cmpO->_scriptId )   dsc->scriptId = _scriptId;
    if ( _closed != cmpO->_closed )       dsc->closed = _closed;
    if ( _lockLevel != cmpO->_lockLevel ) dsc->lockLevel = _lockLevel;
  }
  else
  {
    dsc->lockId = _lockId;
    dsc->locked = _locked;
    dsc->scriptId = _scriptId;
    dsc->closed = _closed;
    dsc->lockLevel = _lockLevel;
  }

  return dsc;
}

Openable::~Openable()
{
}

OpenablePtr Openable::create(DescriptionPtr dsc)
{
  return OpenablePtr(new Openable(dsc));
}

ActorFeature::Type Openable::getType()
{
  return featureType;
}

ActorFeaturePtr Openable::clone()
{
  return OpenablePtr(new Openable(*this));
}

bool Openable::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  OpenablePtr oRhs = std::dynamic_pointer_cast<Openable>(rhs);
  if ( oRhs)
  {
    equal = _lockId == oRhs->_locked;
    equal &= _lockLevel == oRhs->_lockLevel;
    equal &= _scriptId == oRhs->_scriptId;
    equal &= _closed == oRhs->_closed;
  }
  return equal;
}

bool Openable::open(ActorPtr executor)
{
  bool r = false;
  if ( _scriptId > 0 && isClosed() )
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

        _closed = !r;

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

  if ( _scriptId > 0 && !isClosed() )
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

        _closed = r;

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
  return _closed;
}

bool Openable::lock()
{
  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event(EventId::Actor_Locked));
  }
  _locked = true;
  return _locked;
}

bool Openable::unlock()
{
  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event(EventId::Actor_Unlocked));
  }
  _locked = false;
  return !_locked;
}

std::string Openable::getScriptPath() const
{
  return "scripts/openable/" + std::to_string( static_cast<int>(_scriptId) ) + ".lua";
}

bool Openable::isLocked() const
{
  return _locked;
}

int Openable::getLockId() const
{
  return _lockId;
}

int Openable::getLockLevel() const
{
  return _lockLevel;
}

int Openable::getScriptId() const
{
  return _scriptId;
}

}

