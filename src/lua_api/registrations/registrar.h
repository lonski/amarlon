#ifndef CLASS_REGISTRAR
#define CLASS_REGISTRAR

class lua_State;

namespace amarlon { namespace lua_api {

class Registrar
{
public:
  Registrar() = default;
  virtual ~Registrar() = default;

  virtual void reg(lua_State* state) = 0;

};

}}

#endif // CLASS_REGISTRAR

