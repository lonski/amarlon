#ifndef SPELL_PARSER_H
#define SPELL_PARSER_H

#include <persistence/parsers/parser.h>
#include <spell_description.h>

namespace amarlon {

class SpellParser : public Parser
{
public:
  SpellParser() {}
  SpellParser(rapidxml::xml_node<>* xmlNode);

  SpellDescriptionPtr parseSpellDsc();

};

}

#endif // SPELL_PARSER_H
