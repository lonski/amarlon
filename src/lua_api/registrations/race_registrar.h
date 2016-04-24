#ifndef RACE_REGISTRAR_H
#define RACE_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class RaceRegistrar : public Registrar
{
public:
  RaceRegistrar() = default;
  virtual ~RaceRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // RACE_REGISTRAR_H
