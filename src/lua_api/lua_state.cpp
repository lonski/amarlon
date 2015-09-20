#include "lua_state.h"
#include <lua_api/effect_forge.h>

namespace amarlon { namespace lua_api {

LuaState::LuaState()
  : _state(true)
{
  registerClasses();
}

bool LuaState::execute(const std::string &path)
{
  return _state.Load(path);
}

sel::Selector LuaState::operator[](const char* name)
{
  return _state[name];
}

void LuaState::registerClasses()
{
  EffectForge::reg( _state );
}

}}

