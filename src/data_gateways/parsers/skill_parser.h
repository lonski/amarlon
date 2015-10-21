#ifndef SKILL_PARSER_H
#define SKILL_PARSER_H

#include <memory>
#include <data_gateways/parsers/parser.h>

namespace amarlon {

struct SkillDescription;
typedef std::shared_ptr<SkillDescription> SkillDescriptionPtr;


class SkillParser : public Parser
{
public:
  SkillParser() {}
  SkillParser(rapidxml::xml_node<>* xmlNode);

  SkillDescriptionPtr parseSkillDsc();

};

}

#endif // SKILL_PARSER_H
