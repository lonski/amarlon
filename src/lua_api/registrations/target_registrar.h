#ifndef TARGET_REGISTRAR_H
#define TARGET_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class TargetRegistrar : public Registrar
{
public:
  TargetRegistrar() = default;
  virtual ~TargetRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // TARGET_REGISTRAR_H
