#include "status_effect.h"
#include <engine.h>
#include <spell_database.h>
#include <lua_state.h>
namespace amarlon {

StatusEffect::StatusEffect(SpellId spell, int duration)
  : _spell(spell)
  , _duration(duration)
{
}

bool StatusEffect::cancel(Target target)
{
  bool success = false;

  if ( target )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    SpellDatabase& SpellDatabase = Engine::instance().getSpellDatabase();

    if ( lua.execute( SpellDatabase.getScriptPath(_spell) ) )
    {
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
  return _duration;
}

void StatusEffect::setDuration(int duration)
{
  _duration = duration;
}

std::string StatusEffect::getName() const
{
  return Engine::instance().getSpellDatabase().getName(_spell);
}

}
