#include "registration_manager.h"

#include <spelldb_registrar.h>
#include <actor_registrar.h>
#include <damage_registrar.h>
#include <target_registrar.h>
#include <status_effect_registrar.h>
#include <animation_registrar.h>
#include <free_functions_registrar.h>
#include <globals_registrar.h>

namespace amarlon { namespace lua_api {

void RegistrationManager::registerAll(lua_State* state)
{
  SpellDBRegistrar().reg(state);
  ActorRegistrar().reg(state);
  DamageRegistrar().reg(state);
  TargetRegistrar().reg(state);
  StatusEffectRegistrar().reg(state);
  AnimationRegistrar().reg(state);

  FreeFunctionRegistrar().reg(state);
  GlobalsRegistrar().reg(state);

}

}}
