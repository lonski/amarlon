#ifndef MODIFIER_REGISTRAR_H
#define MODIFIER_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class ModifierRegistrar : public Registrar
{
public:
  ModifierRegistrar() = default;
  virtual ~ModifierRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // MODIFIER_REGISTRAR_H
