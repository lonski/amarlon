#include "actor_registrar.h"
#include <lua_state.h>
#include <actor.h>
#include <character.h>
#include <monster.h>
#include <status_effects_manager.h>

namespace amarlon { namespace lua_api {

void ActorRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<ActorPtr>("ActorPtr")
        .def("get", &ActorPtr::get),

      class_<Actor>("Actor")
        .def("getX", &Actor::getX)
        .def("getY", &Actor::getY)
        .def("getStatusEffects", &Actor::getStatusEffects)
        .def("isAllyOf", &Actor::isAllyOf)
        .def("getName", &Actor::getName)
        .def("character", (CharacterPtr(Actor::*)()const)&Actor::getFeature),

      class_<CharacterPtr>("CharacterPtr")
        .def("get", &CharacterPtr::get),

      class_<Character>("Character")
        .def("getLevel", &Character::getLevel )
        .def("takeHeal", &Character::takeHeal )
        .def("takeDamage", &Character::takeDamage )
        .def("setAttackModifier", &Character::setTmpAttackModifier )
        .def("getAttackModifier", &Character::getTmpAttackModifier )
        .def("setSavingThrowModifier", &Character::setTmpSavingThrowModifier )
        .def("getSavingThrowModifier", &Character::getTmpSavingThrowModifier )
        .def("setMoraleModifier", &Character::setTmpMoraleModifier )
        .def("getMoraleModifier", &Character::getTmpMoraleModifier )
  ];
}

}}

