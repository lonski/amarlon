#ifndef STATUS_EFFECT_REGISTRAR_H
#define STATUS_EFFECT_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class StatusEffectRegistrar : public Registrar
{
public:
  StatusEffectRegistrar() = default;
  virtual ~StatusEffectRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // STATUS_EFFECT_REGISTRAR_H
