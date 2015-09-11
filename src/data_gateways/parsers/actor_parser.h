#ifndef ACTORPARSER_H
#define ACTORPARSER_H

#include <map>
#include "actor_descriptions.h"
#include "parsers/parser.h"
#include "actor_feature.h"
#include <effect_parser.h>

namespace amarlon {

class ActorParser : public Parser
{
public:
  ActorParser();
  ActorParser(rapidxml::xml_node<>* xmlNode);

  DescriptionPtr parseFeatureDsc(ActorFeature::Type featureType);

  ActorDescriptionPtr       parseActorDsc();
  InventoryDescriptionPtr   parseInventoryDsc();
  PickableDescriptionPtr    parsePickableDsc();
  CharacterDescriptionPtr   parseCharacterDsc();
  AiDescriptionPtr          parseAiDsc();
  OpenableDescriptionPtr    parseOpenableDsc();
  WearerDescriptionPtr      parseWearerDsc();
  DestroyableDescriptionPtr parseDestroyableDsc();

private:
  std::map<ActorFeature::Type, std::function<DescriptionPtr ()> > _featureParsers;
  EffectParser _effectParser;

  void parseInventoryContentNode(InventoryDescriptionPtr contDsc, rapidxml::xml_node<>* contentNode);
  void mapParsers();

};

}

#endif // ACTORPARSER_H
