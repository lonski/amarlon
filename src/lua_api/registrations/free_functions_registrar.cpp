#include "free_functions_registrar.h"
#include <lua_state.h>
#include <message_box.h>

namespace amarlon {

void log(std::string msg)
{
  printf("%s", msg.c_str());
}

void msg(std::string msg)
{
  gui::msgBox(msg);
}

namespace lua_api {

void FreeFunctionRegistrar::reg(lua_State* state)
{
  using namespace luabind;

  module(state)
  [
      def("log", &log),
      def("msg", &msg)
  ];
}

}}
