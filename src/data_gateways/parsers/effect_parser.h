#ifndef EFFECT_PARSER_H
#define EFFECT_PARSER_H

#include <parsers/parser.h>
#include <effect_description.h>

namespace amarlon {

class EffectParser : public Parser
{
public:
  EffectParser() {}
  EffectParser(rapidxml::xml_node<>* xmlNode);

  EffectDescriptionPtr parseEffectDsc();

};

}

#endif // EFFECT_PARSER_H
