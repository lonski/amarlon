#include "skill_db.h"
#include <fstream>
#include <skill_description.h>
#include <skill.h>

namespace amarlon {

SkillDB::SkillDB()
{
}

SkillDB::~SkillDB()
{
}

std::string SkillDB::getScript(SkillId id) const
{
  return "scripts/skills/" + std::to_string( static_cast<int>(id) ) + ".lua";
}

SkillPtr SkillDB::fetch(SkillId id)
{
  SkillPtr skill;

  if ( id != SkillId::Null )
  {
    skill.reset(new Skill(id));
    auto it = _skills.find(id);
    skill->_flyweight = it != _skills.end() ? it->second : nullptr;
  }

  return skill;
}

bool SkillDB::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');
    parseSkills(buf);

    return true;
  }
  return false;
}

void SkillDB::parseSkills(std::vector<char> &buf)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(&buf[0]);

  rapidxml::xml_node<>* skills    = doc.first_node("Skills");
  rapidxml::xml_node<>* skillNode = skills ? skills->first_node("Skill") : nullptr;

  while(skillNode != nullptr)
  {
    _parser.setSource( skillNode );
    SkillDescriptionPtr dsc = _parser.parseSkillDsc();
    if ( dsc ) _skills[ static_cast<SkillId>(dsc->id) ] = dsc;

    skillNode = skillNode->next_sibling();
  }
}

}
