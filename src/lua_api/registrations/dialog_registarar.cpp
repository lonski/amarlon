#include "dialog_registarar.h"
#include <lua_state.h>
#include <dialog.h>
#include <luabind/iterator_policy.hpp>

namespace amarlon { namespace lua_api {

void DialogRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<Choice>("Choice")
        .def(constructor<>())
        .def_readwrite("id", &Choice::id)
        .def_readwrite("jump", &Choice::jump)
        .def_readwrite("text", &Choice::text),

      class_<Dialog>("Dialog")
        .def(constructor<>())
        .def_readwrite("id", &Dialog::id)
        .def_readwrite("text", &Dialog::text)
        .def_readwrite("choices", &Dialog::choices, return_stl_iterator)
  ];
}

}}
