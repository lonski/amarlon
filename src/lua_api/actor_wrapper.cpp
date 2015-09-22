#include "actor_wrapper.h"
#include <character.h>
#include <actor.h>
#include <engine.h>
#include <lua_state.h>

namespace amarlon { namespace lua_api {

ActorWrapper::ActorWrapper(ActorPtr actor, const char* name)
{
  _actor = ((unsigned long long)actor.get());
  LuaState& state = Engine::instance().getLuaState();
  state[name].SetObj<lua_api::ActorWrapper>( *this,
                                             "getLevel", &lua_api::ActorWrapper::getLevel);
}

ActorWrapper::~ActorWrapper()
{
}

int ActorWrapper::getLevel()
{
  if ( _actor )
  {
    Actor* actor = (Actor*)_actor;
    CharacterPtr character = actor->getFeature<Character>();
    if ( character )
    {
      return character->getLevel();
    }
  }
  return 0;
}

}}

