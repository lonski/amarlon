#include "status_effect.h"
#include <engine.h>
#include <spell_db.h>
#include <lua_state.h>
#include <spell_db.h>
#include <boost/ref.hpp>

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
    SpellDB& spellDb = Engine::instance().getSpellDB();

    if ( lua.execute( spellDb.getScriptPath(_spell) ) )
    {
      try
      {
        success = luabind::call_function<bool>(
            lua()
          , "onCancel"
          , boost::ref(target)
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
  return Engine::instance().getSpellDB().getName(_spell);
}

}
