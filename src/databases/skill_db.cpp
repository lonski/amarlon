#include "skill_db.h"
#include <fstream>
#include <skill_description.h>
#include <skill.h>
#include <engine.h>
#include <module.h>

namespace amarlon {

SkillDB::SkillDB()
{
}

SkillDB::~SkillDB()
{
}

std::string SkillDB::getScript(SkillId id) const
{
  std::string default_script = "scripts/skills/" + std::to_string( static_cast<int>(id) ) + ".lua";
  std::string module_script = Engine::instance().getModule().getPath() + default_script;

  return file_exists(module_script) ? module_script : default_script;
}

std::string SkillDB::getName(SkillId id) const
{
  auto d = fetchDescription(id);
  return d ? d->name : "NoName";
}

SkillPtr SkillDB::fetch(SkillId id)
{
  SkillPtr skill;

  if ( id != SkillId::Null )
  {
    skill.reset(new Skill(id));
    auto d = fetchDescription(id);
    skill->_flyweight = d ? d : nullptr;
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
    parseSkills(buf, _skills);

    return true;
  }
  return false;
}

bool SkillDB::loadPlugin(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');
    parseSkills(buf, _pluginSkills);

    return true;
  }
  return false;
}

void SkillDB::parseSkills(std::vector<char> &buf, std::map<SkillId, SkillDescriptionPtr> &dst)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(&buf[0]);

  rapidxml::xml_node<>* skills    = doc.first_node("Skills");
  rapidxml::xml_node<>* skillNode = skills ? skills->first_node("Skill") : nullptr;

  while(skillNode != nullptr)
  {
    _parser.setSource( skillNode );
    SkillDescriptionPtr dsc = _parser.parseSkillDsc();
    if ( dsc ) dst[ static_cast<SkillId>(dsc->id) ] = dsc;

    skillNode = skillNode->next_sibling();
  }
}

SkillDescriptionPtr SkillDB::fetchDescription(SkillId id) const
{
  auto it = _pluginSkills.find(id);
  if ( it != _pluginSkills.end() )
    return it->second;

  it = _skills.find(id);
  if ( it != _skills.end() )
    return it->second;

  return nullptr;
}

}
