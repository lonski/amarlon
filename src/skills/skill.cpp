#include "skill.h"
#include <engine.h>
#include <lua_state.h>

namespace amarlon {

SkillPtr Skill::create(SkillId id, int level)
{
  return SkillPtr(new Skill(id, level));
}

SkillId Skill::getId() const
{
  return _id;
}

std::string Skill::getScript() const
{
  return "scripts/skills/" + std::to_string( static_cast<int>(_id) ) + ".lua";
}

int Skill::getLevel() const
{
  return _level;
}

std::string Skill::getName() const
{
  return SkillId2Str(_id);
}

bool Skill::use(ActorPtr user, Target target)
{
  bool r = false;

  lua_api::LuaState& lua = Engine::instance().getLuaState();
  if ( lua.execute( getScript() ) )
  {
    try
    {
      r = luabind::call_function<bool>(
          lua()
        , "onUse"
        , user
        , &target
      );
    }
    catch(luabind::error& e)
    {
      lua.logError(e);
    }
  }

  return r;
}

Skill::Skill(SkillId id, int level)
  : _id(id)
  , _level(level)
{
}

}
