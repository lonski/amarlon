#ifndef ACTOR_REGISTRAR_H
#define ACTOR_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class ActorRegistrar : public Registrar
{
public:
  ActorRegistrar() = default;
  virtual ~ActorRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // ACTOR_REGISTRAR_H
