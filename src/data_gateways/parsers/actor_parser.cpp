#include "actor_parser.h"
#include <string>
#include <utils/xml_utils.h>
#include <utils/utils.h>

namespace amarlon {

using namespace rapidxml;
using namespace std;

ActorParser::ActorParser()
{
  mapParsers();
}

  ActorParser::ActorParser(xml_node<> *xmlNode)
 : Parser(xmlNode)
{
  mapParsers();
}

void ActorParser::mapParsers()
{
  _featureParsers[ActorFeature::CONTAINER]   = [&](){ return parseContainerDsc(); };
  _featureParsers[ActorFeature::OPENABLE]    = [&](){ return parseOpenableDsc(); };
  _featureParsers[ActorFeature::PICKABLE]    = [&](){ return parsePickableDsc(); };
  _featureParsers[ActorFeature::FIGHTER]     = [&](){ return parseFighterDsc(); };
  _featureParsers[ActorFeature::WEARER]      = [&](){ return parseWearerDsc(); };
  _featureParsers[ActorFeature::AI]          = [&](){ return parseAiDsc(); };
  _featureParsers[ActorFeature::DESTROYABLE] = [&](){ return parseDestroyableDsc(); };
}

DescriptionPtr ActorParser::parseFeatureDsc(const ActorFeature::Type featureType)
{
  auto it = _featureParsers.find(featureType);
  return it != _featureParsers.end() ? (it->second)() : nullptr;
}

ActorDescriptionPtr ActorParser::parseActorDsc()
{
  ActorDescriptionPtr actorDsc;

  if ( _xml != nullptr )
  {
    actorDsc.reset( new ActorDescription );

    actorDsc->id = (ActorType)getAttribute<int>(_xml, "id");
    actorDsc->name = getAttribute<std::string>(_xml, "name");

    std::string charStr = getAttribute<std::string>(_xml, "character");
    if (charStr.size() > 1 || std::isdigit(charStr[0]))
      actorDsc->character = (unsigned char)std::stol(charStr);
    else
      actorDsc->character = charStr[0];

    string colorStr = getAttribute<std::string>(_xml, "color");
    actorDsc->color = strToColor(colorStr);

    actorDsc->blocks = getAttribute<bool>(_xml, "blocks");
    actorDsc->fovOnly = getAttribute<bool>(_xml, "fovOnly");
    actorDsc->transparent = getAttribute<bool>(_xml, "transparent");

    if ( attributeExists(_xml, "tilePriority") )
      actorDsc->tilePriority = getAttribute<int>(_xml, "tilePriority");
    else
      actorDsc->tilePriority = -1;

  }

  return actorDsc;
}

void ActorParser::parseContainerContentNode(ContainerDescriptionPtr contDsc, xml_node<>* contentNode)
{
  ActorParser aParser(contentNode);
  ContainerDescription::Content cActor;
  ActorDescriptionPtr aDsc = aParser.parseActorDsc();
  if (aDsc != nullptr)
  {
    cActor.actorType = aDsc->id;

    cActor.container = aParser.parseContainerDsc() ;
    cActor.openable = aParser.parseOpenableDsc();
    cActor.pickable = aParser.parsePickableDsc();
    cActor.fighter = aParser.parseFighterDsc();
    cActor.ai = aParser.parseAiDsc();
    cActor.destroyable = aParser.parseDestroyableDsc();

    contDsc->content.push_back( cActor );
  }
}

ContainerDescriptionPtr ActorParser::parseContainerDsc()
{
  ContainerDescriptionPtr contDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* containerNode = _xml->first_node("Container");
    if ( containerNode != nullptr)
    {
      contDsc.reset( new ContainerDescription );

      contDsc->maxSize = getAttribute<int>(containerNode, "maxSize");

      xml_node<>* contentNode = containerNode->first_node("Content");

      while ( contentNode != nullptr)
      {
        parseContainerContentNode(contDsc, contentNode);
        contentNode = contentNode->next_sibling();
      }

    }
  }

  return contDsc;
}

PickableDescriptionPtr ActorParser::parsePickableDsc()
{
  PickableDescriptionPtr pickDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* pickableNode = _xml->first_node("Pickable");
    if (pickableNode != nullptr)
    {
      pickDsc.reset( new PickableDescription );

      pickDsc->stackable = getAttribute<bool>(pickableNode, "stackable");
      pickDsc->amount = getAttribute<int>(pickableNode, "amount");
      if ( pickDsc->amount == 0) pickDsc->amount = 1;
      pickDsc->itemSlot = (ItemSlotType)getAttribute<int>(pickableNode, "itemSlot");
      pickDsc->category = (PickableCategory)getAttribute<int>(pickableNode, "category");

      // == effects == //
      xml_node<>* effectNode = pickableNode->first_node("Effect");
      if ( effectNode != nullptr)
      {
        pickDsc->effect.type = (EffectType)getAttribute<int>(effectNode, "type");
        pickDsc->effect.lockId = getAttribute<int>(effectNode, "lockId");
        pickDsc->effect.uses = getAttribute<int>(effectNode, "uses");
        pickDsc->effect.heal = getAttribute<int>(effectNode, "heal");
      }
    }
  }

  return pickDsc;
}

FighterDescriptionPtr ActorParser::parseFighterDsc()
{
  FighterDescriptionPtr fDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* fighterNode = _xml->first_node("Fighter");
    if (fighterNode != nullptr)
    {
      fDsc.reset( new FighterDescription );

      fDsc->power = getAttribute<float>(fighterNode, "power");
      fDsc->maxHp = getAttribute<float>(fighterNode, "maxHp");
    }
  }

  return fDsc;
}

AiDescriptionPtr ActorParser::parseAiDsc()
{
  AiDescriptionPtr aiDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* aiNode = _xml->first_node("Ai");
    if (aiNode != nullptr)
    {
      aiDsc.reset( new AiDescription );

      aiDsc->type = (AiType)getAttribute<int>(aiNode, "type");
    }
  }

  return aiDsc;
}

OpenableDescriptionPtr ActorParser::parseOpenableDsc()
{
  OpenableDescriptionPtr opDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* openableNode = _xml->first_node("Openable");
    if (openableNode != nullptr)
    {
      opDsc.reset( new OpenableDescription );

      opDsc->type = (OpenableType)getAttribute<int>(openableNode, "type");
      opDsc->lockId = getAttribute<int>(openableNode, "lockId");
      opDsc->locked = getAttribute<bool>(openableNode, "locked");
    }
  }

  return opDsc;
}

WearerDescriptionPtr ActorParser::parseWearerDsc()
{
  WearerDescriptionPtr wrDsc;

  if (_xml != nullptr)
  {
    xml_node<>* wearerNode = _xml->first_node("Wearer");
    if (wearerNode != nullptr)
    {
      wrDsc.reset( new WearerDescription );

      xml_node<>* itemSlotNode = wearerNode->first_node("ItemSlot");
      while (itemSlotNode != nullptr)
      {
        ItemSlotType slot = (ItemSlotType)getAttribute<int>(itemSlotNode, "type");
        wrDsc->itemSlots.push_back(slot);

        xml_node<>* equippedNode = itemSlotNode->first_node("Equipped");
        if (equippedNode != nullptr)
        {
          parseContainerContentNode(wrDsc->eqItems, equippedNode );
        }

        itemSlotNode = itemSlotNode->next_sibling();
      }

      wrDsc->eqItems->maxSize = wrDsc->itemSlots.size();
    }
  }

  return wrDsc;
}

DestroyableDescriptionPtr ActorParser::parseDestroyableDsc()
{
  DestroyableDescriptionPtr destrDsc;

  if (_xml != nullptr)
  {
    xml_node<>* destrNode = _xml->first_node("Destroyable");
    if (destrNode != nullptr)
    {
      destrDsc.reset( new DestroyableDescription );

      xml_node<>* dropRuleNode = destrNode->first_node("DropRule");
      while (dropRuleNode != nullptr)
      {
        DropRule rule;

        rule.dropActorId = static_cast<ActorType>( getAttribute<int>(dropRuleNode, "dropActorId") );
        rule.amountMin = getAttribute<uint32_t>(dropRuleNode, "amountMin");
        rule.amountMax = getAttribute<uint32_t>(dropRuleNode, "amountMax");
        rule.chance = getAttribute<float>(dropRuleNode, "chance");

        destrDsc->dropRules.push_back( rule );

        dropRuleNode = dropRuleNode->next_sibling();
      }

    }
  }

  return destrDsc;
}

}
