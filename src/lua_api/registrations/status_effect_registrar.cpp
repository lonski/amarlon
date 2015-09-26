#include "status_effect_registrar.h"
#include <lua_state.h>
#include <status_effect.h>
#include <status_effects_manager.h>

namespace amarlon { namespace lua_api {

void StatusEffectRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<StatusEffect, std::shared_ptr<StatusEffect> >("StatusEffect")
        .def(constructor<SpellId, int>())
        .def("getDuration", &StatusEffect::getDuration)
        .def("setDuration", &StatusEffect::setDuration)
        .def("getName", &StatusEffect::getName),

      class_<StatusEffectsManager>("StatusEffectsManager")
        .def("add", &StatusEffectsManager::add)
  ];
}

}}

