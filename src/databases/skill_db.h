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
  ~SkillDB();

  std::string getScript(SkillId id) const;
  std::string getName(SkillId id) const;

  SkillPtr fetch(SkillId id);
  bool load(const std::string& fn);
  bool loadPlugin(const std::string& fn);

protected:
  SkillParser _parser;
  std::map<SkillId, SkillDescriptionPtr> _skills;
  std::map<SkillId, SkillDescriptionPtr> _pluginSkills;

  void parseSkills(std::vector<char> &buf, std::map<SkillId, SkillDescriptionPtr>& dst);
  SkillDescriptionPtr fetchDescription(SkillId id) const;

};

}

#endif // SKILL_DB_H
