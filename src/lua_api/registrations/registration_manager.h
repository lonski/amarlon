#ifndef CLASS_REGISTRATION_MANAGER_H
#define CLASS_REGISTRATION_MANAGER_H

#include <memory>
#include <set>
#include <singleton.h>

class lua_State;

namespace amarlon { namespace lua_api {

class RegistrationManager : public Singleton<RegistrationManager>
{
public:
  void registerAll(lua_State* state);

};

}}

#endif // CLASS_REGISTRATION_MANAGER_H
