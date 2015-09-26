#include "spelldb_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <spell_db.h>

namespace amarlon { namespace lua_api {

void SpellDBRegistrar::reg(lua_State* state)
{
  printf("\nSpellDB reg!\n");
  using namespace luabind;
  module( state )
  [
      class_<SpellDB>("SpellDB")
        .def("getName",       &SpellDB::getName)
        .def("getLevel",      &SpellDB::getLevel)
        .def("getRange",      &SpellDB::getRange)
        .def("getClass",      &SpellDB::getClass)
        .def("getTargetType", &SpellDB::getTargetType)
        .def("getRadius",     &SpellDB::getRadius)
  ];
}

}}
