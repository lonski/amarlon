#include "skill_db.h"
#include <fstream>
#include <skill.h>

namespace amarlon {

SkillDB::SkillDB()
{
}

SkillDB::~SkillDB()
{
}

SkillPtr SkillDB::fetch(SkillId id)
{
  if ( id != SkillId::Null )
  {
    auto it = _skills.find(id);
    if ( it != _skills.end() ) return it->second->clone();
  }

  return nullptr;
}

bool SkillDB::load(const std::string &fn)
{
  std::ifstream ifs(fn);
  if ( ifs.is_open() )
  {
    _skills.clear();

    SkillsData skills;
    skills.ParseFromIstream(&ifs);

    for ( auto it = skills.skill().begin(); it != skills.skill().end(); ++it )
    {
      _skills[ static_cast<SkillId>(it->id()) ] = SkillPtr(new Skill(*it));
    }

    return true;
  }
  return false;
}

}
