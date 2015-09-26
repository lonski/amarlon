#include "actor_registrar.h"
#include <lua_state.h>
#include <actor.h>
#include <actor_wrapper.h>

namespace amarlon { namespace lua_api {

void ActorRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<ActorPtr>("Actor")
        .def("get", &ActorPtr::get),

      class_<lua_api::ActorWrapper>("ActorWrapper")
        .def(constructor<ActorPtr>())
        .def("getLevel", &ActorWrapper::getLevel)
        .def("getX", &ActorWrapper::getX)
        .def("getY", &ActorWrapper::getY)
        .def("takeHeal", &ActorWrapper::takeHeal)
        .def("takeDamage", &ActorWrapper::takeDamage)
        .def("setAttackModifier", &ActorWrapper::setAttackModifier)
        .def("setSavingThrowModifier", &ActorWrapper::setSavingThrowModifier)
        .def("setMoraleModifier", &ActorWrapper::setMoraleModifier)
        .def("getAttackModifier", &ActorWrapper::getAttackModifier)
        .def("getSavingThrowModifier", &ActorWrapper::getSavingThrowModifier)
        .def("getMoraleModifier", &ActorWrapper::getMoraleModifier)
        .def("addStatusEffect", &ActorWrapper::addStatusEffect)
        .def("isAllyOf", &ActorWrapper::isAllyOf)
        .def("getName", &ActorWrapper::getName)
  ];
}

}}

