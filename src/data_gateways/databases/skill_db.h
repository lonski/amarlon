#ifndef SKILL_DB_H
#define SKILL_DB_H

#include <memory>
#include <map>
#include <vector>
#include <skill_id.h>
#include <skill_parser.h>

namespace amarlon {

class Skill;
struct SkillDescription;
typedef std::shared_ptr<Skill> SkillPtr;
typedef std::shared_ptr<SkillDescription> SkillDescriptionPtr;

class SkillDB
{
public:
  SkillDB();
  virtual ~SkillDB();

  std::string getScript(SkillId id) const;

  virtual SkillPtr fetch(SkillId id);
  virtual bool load(const std::string& fn);

protected:
  SkillParser _parser;
  std::map<SkillId, SkillDescriptionPtr> _skills;

  void parseSkills(std::vector<char> &buf);

};

}

#endif // SKILL_DB_H
