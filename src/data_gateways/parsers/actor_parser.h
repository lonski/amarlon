#ifndef ACTORPARSER_H
#define ACTORPARSER_H

#include <memory>
#include <string>
#include <data_gateways/parsers/parser.h>

namespace amarlon {

struct ActorDescription;
struct InventoryDescription;
struct PickableDescription;
struct CharacterDescription;
struct AiDescription;
struct OpenableDescription;
struct WearerDescription;
struct DestroyableDescription;
struct TrapDescription;
struct TalkerDescription;

typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;
typedef std::shared_ptr<InventoryDescription> InventoryDescriptionPtr;
typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;
typedef std::shared_ptr<AiDescription> AiDescriptionPtr;
typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;
typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;
typedef std::shared_ptr<DestroyableDescription> DestroyableDescriptionPtr;
typedef std::shared_ptr<TrapDescription> TrapDescriptionPtr;
typedef std::shared_ptr<TalkerDescription> TalkerDescriptionPtr;

class ActorParser : public Parser
{
public:
  ActorParser();
  ActorParser(rapidxml::xml_node<>* xmlNode);

  ActorDescriptionPtr parseDescription();

private:
  InventoryDescriptionPtr   parseInventoryDsc();
  PickableDescriptionPtr    parsePickableDsc();
  CharacterDescriptionPtr   parseCharacterDsc();
  AiDescriptionPtr          parseAiDsc();
  OpenableDescriptionPtr    parseOpenableDsc();
  WearerDescriptionPtr      parseWearerDsc();
  DestroyableDescriptionPtr parseDestroyableDsc();
  TrapDescriptionPtr        parseTrapDsc();
  TalkerDescriptionPtr      parseTalkerDsc();

};

}

#endif // ACTORPARSER_H
