#ifndef GLOBALS_REGISTRAR_H
#define GLOBALS_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class GlobalsRegistrar : public Registrar
{
public:
  GlobalsRegistrar() = default;
  virtual ~GlobalsRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // GLOBALS_REGISTRAR_H
