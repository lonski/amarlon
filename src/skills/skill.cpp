#include "skill.h"
#include <engine.h>
#include <skill_db.h>
#include <lua_state.h>
#include <skill_description.h>
#include <target_type.h>

namespace amarlon {

SkillPtr Skill::create(SkillId id, int level)
{
  SkillPtr skill = Engine::instance().getSkillDB().fetch(id);
  skill->_level = level;
  return skill;
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
  return _flyweight ? _flyweight->name : "";
}

TargetType Skill::getTargetType() const
{
  return _flyweight ? static_cast<TargetType>(_flyweight->target) : TargetType::SELF;
}

int Skill::getRadius() const
{
  return _flyweight ? _flyweight->radius : 0;
}

bool Skill::isPassive() const
{
  return _flyweight ? _flyweight->passive : false;
}

std::string Skill::getDescription() const
{
  return _flyweight ? _flyweight->dsc : "";
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
        , this
      );
    }
    catch(luabind::error& e)
    {
      lua.logError(e);
    }
  }

  return r;
}

bool Skill::operator==(const Skill &rhs) const
{
  return _id == rhs._id && _level == rhs._level;
}

SkillPtr Skill::clone() const
{
  SkillPtr skill( new Skill(_id) );
  skill->_level = _level;
  return skill;
}

Skill::Skill(SkillId id)
  : _id(id)
  , _level(0)
{
}

}
