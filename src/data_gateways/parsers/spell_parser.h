#ifndef SPELL_PARSER_H
#define SPELL_PARSER_H

#include <parsers/parser.h>
#include <spell_description.h>
#include <effect_parser.h>
#include <animation_parser.h>

namespace amarlon {

class SpellParser : public Parser
{
public:
  SpellParser() {}
  SpellParser(rapidxml::xml_node<>* xmlNode);

  SpellDescriptionPtr parseSpellDsc();

private:
  EffectParser _effectParser;
  AnimationParser _animationParser;

};

}

#endif // SPELL_PARSER_H
