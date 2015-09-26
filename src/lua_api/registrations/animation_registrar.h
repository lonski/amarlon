#ifndef ANIMATION_REGISTRAR_H
#define ANIMATION_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class AnimationRegistrar : public Registrar
{
public:
  AnimationRegistrar() = default;
  virtual ~AnimationRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // ANIMATION_REGISTRAR_H
