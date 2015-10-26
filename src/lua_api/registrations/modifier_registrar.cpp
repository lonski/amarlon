#include "modifier_registrar.h"
#include <lua_state.h>
#include <modifier.h>
#include <converters.h>

namespace amarlon { namespace lua_api {

void ModifierRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<ModifierType>("ModifierType")
        .def_readwrite("savingThrow", &ModifierType::savingThrow)
        .def_readwrite("generic", &ModifierType::generic)
        .def_readwrite("dmg",  &ModifierType::dmg)
        .def_readwrite("ac",  &ModifierType::ac)
        .def_readwrite("skill",  &ModifierType::skill),

      class_<Modifier>("Modifier")
        .def(constructor<int>())
        .def_readwrite("Value", &Modifier::Value)
        .def_readwrite("Type",  &Modifier::Type)
  ];
}

}}
