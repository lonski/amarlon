#ifndef ACTOR_WRAPPER_H
#define ACTOR_WRAPPER_H

#include <memory>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

namespace lua_api {

class ActorWrapper
{
public:
  /**
   * @brief Registers an actor instance to Lua State
   * @param actor - actor's instance to be registered
   * @param name - object name visible in scripts
   */
  ActorWrapper(ActorPtr actor, const char* name);
  ~ActorWrapper();

  int getLevel();

private:
  Actor** _actor;

};

}}

#endif // ACTOR_WRAPPER_H
