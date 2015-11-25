#ifndef RPG_PARSER_H
#define RPG_PARSER_H

#include <memory>
#include <race.h>
#include <character_class.h>
#include <persistence/parsers/parser.h>

namespace amarlon {

class RpgParser : public Parser
{
public:
  RpgParser() {}
  RpgParser(rapidxml::xml_node<>* xmlNode);

  std::vector<RacePtr> parseRaces();
  std::vector<CharacterClassPtr> parseCharacterClasses();

};

}

#endif // RPG_PARSER_H
