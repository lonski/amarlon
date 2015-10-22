#include "skill_parser.h"
#include <skill_description.h>
#include <xml_utils.h>

namespace amarlon {

SkillParser::SkillParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

SkillDescriptionPtr SkillParser::parseSkillDsc()
{
  SkillDescriptionPtr skillDsc;

  if ( _xml != nullptr)
  {
    skillDsc.reset( new SkillDescription );

    skillDsc->name = getAttribute<std::string>(_xml, "name");
    skillDsc->dsc = getAttribute<std::string>(_xml, "description");
    skillDsc->id = getAttribute<int>(_xml, "id");
    skillDsc->target = getAttribute<int>(_xml, "targetType");
    skillDsc->radius = getAttribute<int>(_xml, "radius");
    skillDsc->passive = getAttribute<bool>(_xml, "passive");
  }

  return skillDsc;
}

}

