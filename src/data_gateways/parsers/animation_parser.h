#ifndef ANIMATION_PARSER_H
#define ANIMATION_PARSER_H

#include <data_gateways/parsers/parser.h>
#include <animation_description.h>

namespace amarlon {

class AnimationParser : public Parser
{
public:
  AnimationParser() {}
  AnimationParser(rapidxml::xml_node<>* xmlNode);

  AnimationDescriptionPtr parseAnimationDsc();

};

}

#endif // ANIMATION_PARSER_H
