#include "skill_registrar.h"
#include <lua_state.h>
#include <skill.h>
#include <converters.h>

namespace amarlon { namespace lua_api {

void SkillRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<Skill>("Skill")
        .def("getScript", &Skill::getScript)
        .def("getId", &Skill::getId)
        .def("getLevel", &Skill::getLevel)
        .def("getName", &Skill::getName)
  ];
}

}}
