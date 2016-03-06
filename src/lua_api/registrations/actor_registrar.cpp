#include "actor_registrar.h"
#include <converters.h>
#include <lua_state.h>
#include <actor.h>
#include <character.h>
#include <openable.h>
#include <trap.h>
#include <ai.h>
#include <status_effects_manager.h>
#include <iterator_policy.hpp>
#include <talker.h>
#include <inventory.h>
#include <actor_db.h>

namespace amarlon { namespace lua_api {

void ActorRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<ActorDB>("ActorDB")
        .def("fetch", &ActorDB::fetch),

      class_<ActorPtr>("ActorPtr")
        .def(constructor<>())
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
        .def("notify", &Actor::notify )
        .def("character", (CharacterPtr(Actor::*)()const)&Actor::getFeature)
        .def("trap", (TrapPtr(Actor::*)()const)&Actor::getFeature)
        .def("openable", (OpenablePtr(Actor::*)()const)&Actor::getFeature)
        .def("ai", (AiPtr(Actor::*)()const)&Actor::getFeature)
        .def("inventory", (InventoryPtr(Actor::*)()const)&Actor::getFeature)
        .def("getMap", &Actor::getMap)
        .def("isInFov", &Actor::isInFov)
        .def("isHostileTo", &Actor::isHostileTo),

      class_<CharacterPtr>("CharacterPtr")
        .def("get", &CharacterPtr::get),

      class_<Character>("Character")
        .def("getLevel", &Character::getLevel )
        .def("takeHeal", &Character::takeHeal )
        .def("takeDamage", &Character::takeDamage )
        .def("rollSavingThrow", &Character::rollSavingThrow )
        .def("abilityRoll", &Character::abilityRoll )
        .def("getArmorClass", &Character::getArmorClass )
        .def("addModifier", &Character::addModifier)
        .def("removeModifier", &Character::removeModifier),

      class_<OpenablePtr>("OpenablePtr")
        .def("get", &OpenablePtr::get),

      class_<Openable>("Openable")
        .def("isLocked", &Openable::isLocked )
        .def("getLockId", &Openable::getLockId )
        .def("lock", &Openable::lock )
        .def("unlock", &Openable::unlock )
        .def("getLockLevel", &Openable::getLockLevel ),

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
        .def("setDetected",   &Trap::setDetected)
        .def("isDetected",    &Trap::isDetected),

      class_<AiPtr>("AiPtr")
        .def("get", &AiPtr::get),

      class_<Ai>("Ai")
        .def("performAction", &Ai::performAction )
        .def("isSleeping", &Ai::isSleeping )
        .def("wakeUp", &Ai::wakeUp )
        .def("isHiding", &Ai::isHiding )
        .def("setHiding", &Ai::setHiding )
        .def("canOperate", &Ai::canOperate )
        .def("isSneaking", &Ai::isSneaking )
        .def("setSneaking", &Ai::setSneaking )
        .def("changeState", &Ai::changeState )
        .def("getCurrentState", &Ai::getCurrentState)
        .def("getEnemiesInFov", &Ai::getEnemiesInFov)
        .def("isHunting", &Ai::isHunting)
        .def("setTarget", (void(Ai::*)(ActorPtr))&Ai::setTarget )
        .def("hasTarget", &Ai::hasTarget )
        .def("getTarget", &Ai::getTarget ),

      class_<TalkerPtr>("TalkerPtr")
        .def("get", &TalkerPtr::get),

      class_<Talker>("Talker")
        .def("getId", &Talker::getId),

      class_<InventoryPtr>("InventoryPtr")
        .def("get", &InventoryPtr::get),

      class_<Inventory>("Inventory")
        .def("add", &Inventory::add)
        .def("remove", &Inventory::remove)
        .def("getGoldAmount", &Inventory::getGoldAmount)
        .def("modifyGoldAmount", &Inventory::modifyGoldAmount)

  ];
}

}}


