#include "status_effect.h"
#include <engine.h>
#include <spell.h>
#include <lua_state.h>

namespace amarlon {

StatusEffect::StatusEffect(const std::string& name, const std::string& script, int duration)
{
  _data.set_name(name);
  _data.set_script(script);
  _data.set_duration(duration);
}

StatusEffect::StatusEffect(const StatusEffectData &data)
{
  _data.CopyFrom(data);
}

StatusEffect::StatusEffect(const StatusEffect &e)
{
  *this = e;
}

void StatusEffect::operator=(const StatusEffect &rhs)
{
  _data.CopyFrom(rhs._data);
}

bool StatusEffect::cancel(Target target)
{
  bool success = false;

  if ( target && !getScript().empty() )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( getScript() ) )
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

int StatusEffect::getDuration() const
{
  return _data.duration();
}

void StatusEffect::setDuration(int duration)
{
  _data.set_duration(duration);
}

std::string StatusEffect::getName() const
{
  return _data.name();
}

std::string StatusEffect::getScript() const
{
  return _data.script();
}

bool StatusEffect::operator==(const StatusEffect &rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

const StatusEffectData &StatusEffect::getData() const
{
  return _data;
}

}
