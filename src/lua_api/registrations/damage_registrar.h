#ifndef DAMAGE_REGISTRAR_H
#define DAMAGE_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class DamageRegistrar : public Registrar
{
public:
  DamageRegistrar() = default;
  virtual ~DamageRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // DAMAGE_REGISTRAR_H
