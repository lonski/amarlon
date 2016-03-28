#include "spelldb_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <spell_db.h>
#include <spell.h>

namespace amarlon { namespace lua_api {

void SpellDBRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<SpellDB>("SpellDB")
        .def("fetch",         &SpellDB::fetch),

      class_<SpellPtr>("SpellPtr")
        .def("get", &SpellPtr::get),

      class_<Spell>("Spell")
        .def("getName",       &Spell::getName)
        .def("getLevel",      &Spell::getLevel)
        .def("getRange",      &Spell::getRange)
        .def("getClass",      &Spell::getClass)
        .def("getTargetType", &Spell::getTargetType)
        .def("getRadius",     &Spell::getRadius)
        .def("getScript",     &Spell::getScript)


  ];
}

}}
