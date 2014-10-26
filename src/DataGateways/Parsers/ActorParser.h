#ifndef ACTORPARSER_H
#define ACTORPARSER_H

#include "../ActorDescriptions.h"
#include "xml/rapidxml.hpp"

namespace amarlon {

class ActorParser
{
public:
  ActorParser();
  ActorParser(rapidxml::xml_node<>* xmlNode);

  void setSource(rapidxml::xml_node<>* xmlNode);

  ActorDescription*     parseActorDsc();
  ContainerDescription* parseContainerDsc();
  PickableDescription*  parsePickableDsc();
  FighterDescription*   parseFighterDsc();
  AiDescription*        parseAiDsc();
  OpenableDescription*  parseOpenableDsc();
  WearerDescription*    parseWearerDsc();

private:
  rapidxml::xml_node<>* _xml;

  void parseContainerContentNode(ContainerDescription* contDsc, rapidxml::xml_node<>* contentNode);

};

}

#endif // ACTORPARSER_H
