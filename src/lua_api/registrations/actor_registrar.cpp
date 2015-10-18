#include "actor_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <actor.h>
#include <character.h>
#include <openable.h>
#include <trap.h>
#include <status_effects_manager.h>

namespace amarlon { namespace lua_api {

void ActorRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<ActorPtr>("ActorPtr")
        .def("get", &ActorPtr::get),

      class_<ActorWPtr>("ActorWPtr")
        .def("lock", &ActorWPtr::lock),

      class_<Actor>("Actor")
        .def("getX", &Actor::getX)
        .def("getY", &Actor::getY)
        .def("getStatusEffects", &Actor::getStatusEffects)
        .def("isAllyOf", &Actor::isAllyOf)
        .def("getName", &Actor::getName)
        .def("setName", &Actor::setName)
        .def("getType", &Actor::getType)
        .def("setType", &Actor::setType)      
        .def("getSymbol", &Actor::getSymbol)
        .def("setSymbol", &Actor::setSymbol)
        .def("morph", &Actor::morph)
        .def("isBlocking", &Actor::isBlocking )
        .def("setBlocking", &Actor::setBlocking )
        .def("isTransparent", &Actor::isTransparent )
        .def("setTransparent", &Actor::setTransparent )
        .def("isFovOnly", &Actor::isFovOnly )
        .def("setFovOnly", &Actor::setFovOnly )
        .def("character", (CharacterPtr(Actor::*)()const)&Actor::getFeature)
        .def("trap", (TrapPtr(Actor::*)()const)&Actor::getFeature)
        .def("openable", (OpenablePtr(Actor::*)()const)&Actor::getFeature),

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
        .def("setArmorModifier", &Character::setTmpArmorClassModifier )
        .def("getArmorModifier", &Character::getTmpArmorClassModifier )
        .def("rollSavingThrow", &Character::rollSavingThrow )
        .def("getArmorClass", &Character::getArmorClass ),

      class_<OpenablePtr>("OpenablePtr")
        .def("get", &OpenablePtr::get),

      class_<Openable>("Openable")
        .def("isLocked", &Openable::isLocked )
        .def("getLockId", &Openable::getLockId )
        .def("lock", &Openable::lock )
        .def("unlock", &Openable::unlock ),

      class_<TrapPtr>("TrapPtr")
        .def("get", &TrapPtr::get),

      class_<Trap>("Trap")
        .def("isArmed",       &Trap::isArmed )
        .def("setArmed",      &Trap::setArmed )
        .def("getId",         &Trap::getId )
        .def("getScript",     &Trap::getScript )
        .def("getDifficulty", &Trap::getDifficulty )
        .def("getOwner",      &Trap::getOwner )
        .def("getName",       &Trap::getName )

  ];
}

}}

