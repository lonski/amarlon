#ifndef SKILL_DB_H
#define SKILL_DB_H

#include <memory>
#include <map>
#include <vector>
#include <skill_id.h>
#include <skill.pb.h>

namespace amarlon {

class Skill;
typedef std::shared_ptr<Skill> SkillPtr;

class SkillDB
{
public:
  SkillDB();
  virtual ~SkillDB();

  virtual SkillPtr fetch(SkillId id);
  virtual bool load(const std::string& fn);

protected:
  std::map<SkillId, SkillPtr> _skills;

};

}

#endif // SKILL_DB_H
