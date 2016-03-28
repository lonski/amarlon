#include "skill.h"
#include <engine.h>
#include <skill_db.h>
#include <lua_state.h>
#include <target_type.h>


namespace amarlon {

Skill::Skill(const SkillData &data)
{
  _data.CopyFrom(data);
}

Skill::Skill(const Skill& skill)
{
  *this = skill;
}

SkillPtr Skill::create(SkillId id)
{
  return Engine::instance().getSkillDB().fetch(id);
}

SkillPtr Skill::clone() const
{
  return SkillPtr( new Skill(*this) );
}

Skill &Skill::operator=(const Skill &skill)
{
  if ( this != &skill )  _data.CopyFrom(skill._data);
  return *this;
}

bool Skill::operator==(const Skill &rhs)
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

SkillId Skill::getId() const
{
  return static_cast<SkillId>(_data.id());
}

std::string Skill::getScript() const
{
  return "scripts/skills/" + std::to_string( static_cast<int>( _data.id() ) ) + ".lua";
}

int Skill::getLevel() const
{
  return _data.level();
}

void Skill::setLevel(int level)
{
  _data.set_level(level);
}

std::string Skill::getName() const
{
  return _data.name();
}

TargetType Skill::getTargetType() const
{
  return static_cast<TargetType>(_data.target_type());
}

int Skill::getRadius() const
{
  return _data.radius();
}

bool Skill::isPassive() const
{
  return _data.passive();
}

std::string Skill::getDescription() const
{
  return _data.description();
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

}
