#ifndef ACTORPARSER_H
#define ACTORPARSER_H

#include <map>
#include "../ActorDescriptions.h"
#include <Parsers/parser.h>
#include <actor_feature.h>

namespace amarlon {

class ActorParser : public Parser
{
public:
  ActorParser();
  ActorParser(rapidxml::xml_node<>* xmlNode);

  Description* parseFeatureDsc(ActorFeature::Type featureType);

  ActorDescription*     parseActorDsc();
  ContainerDescription* parseContainerDsc();
  PickableDescription*  parsePickableDsc();
  FighterDescription*   parseFighterDsc();
  AiDescription*        parseAiDsc();
  OpenableDescription*  parseOpenableDsc();
  WearerDescription*    parseWearerDsc();

private:
  std::map<ActorFeature::Type, std::function<Description* ()> > _featureParsers;

  void parseContainerContentNode(ContainerDescription* contDsc, rapidxml::xml_node<>* contentNode);
  void mapParsers();

};

}

#endif // ACTORPARSER_H
