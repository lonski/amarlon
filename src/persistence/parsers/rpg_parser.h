#ifndef RPG_PARSER_H
#define RPG_PARSER_H

#include <memory>
#include <vector>
#include <persistence/parsers/parser.h>

namespace amarlon {

struct RaceDescription;
struct CharacterClassDescription;
typedef std::shared_ptr<RaceDescription> RaceDescriptionPtr;
typedef std::shared_ptr<CharacterClassDescription> CharacterClassDescriptionPtr;

class RpgParser : public Parser
{
public:
  RpgParser() {}
  RpgParser(rapidxml::xml_node<>* xmlNode);

  std::vector<CharacterClassDescriptionPtr> parseCharacterClasses();
  std::vector<RaceDescriptionPtr> parseRaces();

};

}

#endif // RPG_PARSER_H
