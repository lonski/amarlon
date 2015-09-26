#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <string>
#include <memory>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>

namespace amarlon {

namespace lua_api {

class LuaState
{
public:
  LuaState();
  ~LuaState();

  /**
   * @brief Executes script file from given path
   */
  bool execute(const std::string& path);
  lua_State* operator()() const;

  void registerAPI();
  void logError(const luabind::error& e) const;

private:
  lua_State* _state;


};

}}

#endif // SCRIPT_MANAGER_H
