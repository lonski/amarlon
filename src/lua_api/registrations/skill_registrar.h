#ifndef SKILL_REGISTRAR_H
#define SKILL_REGISTRAR_H

#include <registrar.h>

namespace amarlon { namespace lua_api {

class SkillRegistrar : public Registrar
{
public:
  SkillRegistrar() = default;
  virtual ~SkillRegistrar() = default;

  virtual void reg(lua_State* state);

};

}}

#endif // SKILL_REGISTRAR_H
