#include "status_effect.h"
#include <engine.h>
#include <spell.h>
#include <lua_state.h>

namespace amarlon {

StatusEffect::StatusEffect(SpellId spell, int duration)
  : _spell( Spell::create(spell) )
  , _duration(duration)
{
}

bool StatusEffect::cancel(Target target)
{
  bool success = false;

  if ( target )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( Spell::getScriptPath( getSpellId() ) ) )
    {
      try
      {
        success = luabind::call_function<bool>(
            lua()
          , "onCancel"
          , &target
          , _spell.get()
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
  return _spell->getName();
}

SpellId StatusEffect::getSpellId() const
{
  return _spell->getId();
}

bool StatusEffect::operator==(const StatusEffect &rhs)
{
  return _spell->getId() == rhs.getSpellId();
}

}
