#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include <string>
#include <memory>
#include <selene.h>

namespace amarlon {

namespace lua_api {

class LuaState
{
public:
  LuaState();

  /**
   * @brief Executes script file from given path
   */
  bool execute(const std::string& path);

  sel::Selector operator[](const char *name);

private:
  sel::State _state;

  void registerClasses();

};

}}

#endif // SCRIPT_MANAGER_H
