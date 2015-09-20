#include "lua_state.h"
#include <lua_api/effect_forge.h>

namespace amarlon { namespace lua_api {

LuaState::LuaState()
{
  registerClasses();
}

bool LuaState::execute(const std::__cxx11::string &path)
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

