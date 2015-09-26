#include "globals_registrar.h"
#include <lua_state.h>
#include <engine.h>
#include <spell_db.h>

namespace amarlon { namespace lua_api {

void GlobalsRegistrar::reg(lua_State* state)
{
  luabind::globals(state)["SpellDB"] = &Engine::instance().getSpellDB();
}

}}
