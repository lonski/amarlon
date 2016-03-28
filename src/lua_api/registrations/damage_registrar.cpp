#include "damage_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <damage.h>

namespace amarlon { namespace lua_api {

void DamageRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<Damage>("Damage")
        .def(constructor<const std::string&>())
        .def_readwrite("value", &Damage::value)
        .def_readwrite("diceCount", &Damage::diceCount)
        .def_readwrite("dice", &Damage::dice)
        .def_readwrite("type", &Damage::type)
        .def("roll", &Damage::roll)
  ];
}

}}
