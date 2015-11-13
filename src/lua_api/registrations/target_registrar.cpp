#include "target_registrar.h"
#include <lua_state.h>
#include <target.h>
#include <luabind/iterator_policy.hpp>

namespace amarlon { namespace lua_api {

void TargetRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<Target>("Target")
        .def(constructor<>())
        .def_readwrite("x", &Target::x)
        .def_readwrite("y", &Target::y)
        .def_readwrite("actors", &Target::actors, return_stl_iterator)
        .def("getFirstActor", (ActorPtr(Target::*)()const)&Target::firstActor )
  ];
}

}}
