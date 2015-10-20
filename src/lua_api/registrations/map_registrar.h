#ifndef MAP_REGISTRAR_H
#define MAP_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class MapRegistrar : public Registrar
{
public:
  MapRegistrar() = default;
  virtual ~MapRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // MAP_REGISTRAR_H
