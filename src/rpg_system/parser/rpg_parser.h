#ifndef RPG_PARSER_H
#define RPG_PARSER_H

#include <memory>
#include <vector>
#include <xml/rapidxml.hpp>

namespace amarlon {

struct RaceDescription;
struct CharacterClassDescription;
typedef std::shared_ptr<RaceDescription> RaceDescriptionPtr;
typedef std::shared_ptr<CharacterClassDescription> CharacterClassDescriptionPtr;

class RpgParser
{
public:
  RpgParser(rapidxml::xml_node<>* xmlNode = nullptr);

  void setSource(rapidxml::xml_node<>* xmlNode);

  std::vector<CharacterClassDescriptionPtr> parseCharacterClasses();
  std::vector<RaceDescriptionPtr> parseRaces();

private:
  rapidxml::xml_node<>* _xml;

};

}

#endif // RPG_PARSER_H
