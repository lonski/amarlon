#ifndef DIALOG_REGISTARAR_H
#define DIALOG_REGISTARAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class DialogRegistrar : public Registrar
{
public:
  DialogRegistrar() = default;
  virtual ~DialogRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // DIALOG_REGISTARAR_H
