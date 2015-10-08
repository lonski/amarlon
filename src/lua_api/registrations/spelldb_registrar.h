#ifndef SPELL_DB_H
#define SPELL_DB_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class SpellDatabaseRegistrar : public Registrar
{
public:
  SpellDatabaseRegistrar() = default;
  virtual ~SpellDatabaseRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // SPELL_DB_H
