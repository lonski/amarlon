#include "race_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <race.h>

namespace amarlon { namespace lua_api {

void RaceRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<Race>("Race")
        .def("getType", &Race::getType)
        .def("getName", &Race::getName)
        .def("isPlayable", &Race::isPlayable),

      class_<RacePtr>("RacePtr")
        .def("get", &RacePtr::get)
  ];
}

}}
