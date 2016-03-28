#include "lua_state.h"
#include <registration_manager.h>
#include <engine.h>
#include <message_box.h>

namespace amarlon {

namespace lua_api {

LuaState::LuaState()
  : _state(nullptr)
{
  _state = luaL_newstate();
  luaL_openlibs(_state);
  luabind::open(_state);
}

LuaState::~LuaState()
{
  lua_close(_state);
}

bool LuaState::execute(const std::string &path)
{
  if (luaL_dofile(_state, path.c_str()) != 0)
  {
      gui::msgBox(lua_tostring(_state, -1), gui::MsgType::Error);
      return false;
  }
  return true;
}

lua_State* LuaState::operator()() const
{
  return _state;
}

void LuaState::registerAPI()
{
  RegistrationManager::instance().registerAll(_state);
}

void LuaState::logError(const luabind::error &e) const
{
  luabind::object error_msg(luabind::from_stack(e.state(), -1));
  std::ostringstream str;
  str << "Lua run-time error: \n" << error_msg;
  gui::msgBox(str.str(), gui::MsgType::Error);
}

void LuaState::logError(const std::exception &e) const
{
  std::ostringstream str;
  str << "Error when executing script: \n" << e.what();
  gui::msgBox(str.str(), gui::MsgType::Error);
}

}}
