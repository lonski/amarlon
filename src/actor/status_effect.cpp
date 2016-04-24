#include "status_effect.h"
#include <engine.h>
#include <spell.h>
#include <lua_state.h>

namespace amarlon {

StatusEffect::StatusEffect(const std::string& name, const std::string& script, int duration)
  : _name( name )
  , _script( script )
  , _duration( duration )
{
}

bool StatusEffect::cancel(Target target)
{
  bool success = false;

  if ( target && !_script.empty() )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( _script ) && lua.function_exists("onCancel") )
    {
      target.actors.erase( std::remove_if(target.actors.begin(), target.actors.end(),[](ActorPtr a){
                             return a == nullptr;
                           }));

      try
      {
        success = luabind::call_function<bool>(
            lua()
          , "onCancel"
          , &target
        );
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }

  }

  return success;
}

bool StatusEffect::tickDay(Target target)
{
  bool success = false;

  if ( target && !_script.empty() )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( _script ) && lua.function_exists("onDayTick") )
    {
      target.actors.erase( std::remove_if(target.actors.begin(), target.actors.end(),[](ActorPtr a){
                             return a == nullptr;
                           }));

      try
      {
        success = luabind::call_function<bool>(
            lua()
          , "onDayTick"
          , &target
        );
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }

  }

  return success;
}

int StatusEffect::getDuration() const
{
  return _duration;
}

void StatusEffect::setDuration(int duration)
{
  _duration = duration;
}

std::string StatusEffect::getName() const
{
  return _name;
}

std::string StatusEffect::getScript() const
{
  return _script;
}

bool StatusEffect::operator==(const StatusEffect &rhs)
{
  return _script == rhs._script &&
         _name == rhs._name;
}

}
