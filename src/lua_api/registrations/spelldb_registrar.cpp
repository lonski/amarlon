#include "spelldb_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <spell_database.h>

namespace amarlon { namespace lua_api {

void SpellDatabaseRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<SpellDatabase>("SpellDatabase")
        .def("getName",       &SpellDatabase::getName)
        .def("getLevel",      &SpellDatabase::getLevel)
        .def("getRange",      &SpellDatabase::getRange)
        .def("getClass",      &SpellDatabase::getClass)
        .def("getTargetType", &SpellDatabase::getTargetType)
        .def("getRadius",     &SpellDatabase::getRadius)
  ];
}

}}
