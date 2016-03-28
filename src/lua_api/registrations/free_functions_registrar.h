#ifndef FREE_FUNCTIONS_REGISTRAR_H
#define FREE_FUNCTIONS_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class FreeFunctionRegistrar : public Registrar
{
public:
  FreeFunctionRegistrar() = default;
  virtual ~FreeFunctionRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // FREE_FUNCTIONS_REGISTRAR_H
