#include "openable.h"
#include <amarlon_except.h>
#include <actor_descriptions.h>
#include <actor.h>
#include <lua_state.h>
#include <engine.h>
#include <message_box.h>
#include <module.h>

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
    if ( oDsc->lockId )      _lockId      = *oDsc->lockId;
    if ( oDsc->lockLevel )   _lockLevel   = *oDsc->lockLevel;
    if ( oDsc->locked )      _locked      = *oDsc->locked;
    if ( oDsc->scriptId )    _scriptId    = *oDsc->scriptId;
    if ( oDsc->closed )      _closed      = *oDsc->closed;
    if ( oDsc->openedState ) _openedState = *oDsc->openedState;
    if ( oDsc->closedState ) _closedState = *oDsc->closedState;
  }

  isClosed() ? applyState(_closedState) : applyState(_openedState);
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
    if ( _openedState != cmpO->_openedState ) dsc->openedState = _openedState;
    if ( _closedState != cmpO->_closedState ) dsc->closedState = _closedState;
  }
  else
  {
    dsc->lockId = _lockId;
    dsc->locked = _locked;
    dsc->scriptId = _scriptId;
    dsc->closed = _closed;
    dsc->lockLevel = _lockLevel;
    dsc->openedState = _openedState;
    dsc->closedState = _closedState;
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
    equal &= _openedState == oRhs->_openedState;
    equal &= _closedState == oRhs->_closedState;
  }
  return equal;
}

bool Openable::executeScript(const std::string &fun, ActorPtr executor)
{
  bool r = true;

  if ( _scriptId > 0 )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();

    if ( lua.execute( getScriptPath() ) )
    {
      try
      {
        r = luabind::call_function<bool>(
            lua()
          , fun.c_str()
          , executor
          , getOwner().lock()
        );
      }
      catch(luabind::error& e)
      {
        r = false;
        lua.logError(e);
      }
    }
  }

  return r;
}

bool Openable::applyState(const OpenableState& state)
{
  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    owner->setSymbol( state.symbol );
    owner->setTransparent( state.transparent );
    owner->setBlocking( state.blocks );
    return true;
  }
  return false;
}

bool Openable::open(ActorPtr executor)
{
  bool r = false;

  if ( isClosed() )
  {
    if ( applyState(_openedState) && executeScript("onOpen", executor) )
    {
      r = true;
      _closed = false;

      ActorPtr owner = getOwner().lock();
      if ( owner ) owner->interract(executor);
    }
  }

  return r;
}

bool Openable::close(ActorPtr executor)
{
  bool r = false;

  if ( !isClosed() )
  {
    if ( applyState(_closedState) && executeScript("onClose", executor) )
    {
      r = true;
      _closed = true;

      ActorPtr owner = getOwner().lock();
      if ( owner ) owner->interract(executor);
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

std::string Openable::debug(const std::string &linebreak)
{
  std::string d = " " + linebreak + "-----OPENABLE-----"+linebreak;

  d += "Locked = " + std::string( _locked ? "True" : "False") + linebreak;
  d += "LockId = " + toStr(_lockId)  + linebreak;
  d += "Lock level = " + toStr(_lockLevel)  + linebreak;
  d += "Closed = " + std::string( _closed ? "True" : "False") + linebreak;
  d += "Script ID = " + toStr(_scriptId)  + linebreak;

  d += ">>> Opened State" + linebreak;
  d += "    Symbol = " + std::string(1, _openedState.symbol) + linebreak;
  d += "    Blocks = " + std::string( _openedState.blocks ? "True" : "False") + linebreak;
  d += "    Transparent = " + std::string( _openedState.transparent ? "True" : "False") + linebreak;

  d += ">>> Closed State" + linebreak;
  d += "    Symbol = " + std::string(1, _closedState.symbol) + linebreak;
  d += "    Blocks = " + std::string( _closedState.blocks ? "True" : "False") + linebreak;
  d += "    Transparent = " + std::string( _closedState.transparent ? "True" : "False") + linebreak;

  d += "----------------" + linebreak;

  return d;
}

std::string Openable::getScriptPath() const
{
  std::string default_script = "scripts/openable/" + std::to_string( static_cast<int>(_scriptId) ) + ".lua";
  std::string module_script = Engine::instance().getModule().getPath() + default_script;

  return file_exists(module_script) ? module_script : default_script;
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

