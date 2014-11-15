#ifndef ACTORPARSER_H
#define ACTORPARSER_H

#include "../ActorDescriptions.h"
#include <Parsers/parser.h>

namespace amarlon {

class ActorParser : public Parser
{
public:
  ActorParser() = default;
  ActorParser(rapidxml::xml_node<>* xmlNode);

  ActorDescription*     parseActorDsc();
  ContainerDescription* parseContainerDsc();
  PickableDescription*  parsePickableDsc();
  FighterDescription*   parseFighterDsc();
  AiDescription*        parseAiDsc();
  OpenableDescription*  parseOpenableDsc();
  WearerDescription*    parseWearerDsc();

private:
  void parseContainerContentNode(ContainerDescription* contDsc, rapidxml::xml_node<>* contentNode);

};

}

#endif // ACTORPARSER_H
