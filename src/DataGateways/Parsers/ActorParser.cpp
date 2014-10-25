#include "ActorParser.h"
#include "Utils/XmlUtils.h"
#include "Utils/Utils.h"
#include <string>

namespace amarlon {

using namespace rapidxml;
using namespace std;

ActorParser::ActorParser()
 : _xml(nullptr)
{
}

ActorParser::ActorParser(xml_node<> *xmlNode)
 : _xml(xmlNode)
{
}

void ActorParser::setSource(xml_node<> *xmlNode)
{
  _xml = xmlNode;
}

ActorDescription *ActorParser::parseActorDsc()
{
  ActorDescription* actorDsc = nullptr;

  if ( _xml != nullptr )
  {
    actorDsc = new ActorDescription;

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
  }

  return actorDsc;
}

ContainerDescription *ActorParser::parseContainerDsc()
{
  ContainerDescription* contDsc = nullptr;

  if ( _xml != nullptr )
  {
    xml_node<>* containerNode = _xml->first_node("Container");
    if ( containerNode )
    {
      contDsc = new ContainerDescription;

      contDsc->maxSize = getAttribute<int>(containerNode, "maxSize");

      xml_node<>* contentNode = containerNode->first_node("Content");
      ActorParser aParser;
      while ( contentNode )
      {
        aParser.setSource(contentNode);

        ContainerDescription::Content cActor;
        ActorDescription* aDsc = aParser.parseActorDsc();
        if (aDsc != nullptr)
        {
          cActor.actorType = aDsc->id;

          cActor.container = aParser.parseContainerDsc();
          cActor.openable  = aParser.parseOpenableDsc();
          cActor.pickable  = aParser.parsePickableDsc();
          cActor.fighter   = aParser.parseFighterDsc();
          cActor.ai        = aParser.parseAiDsc();

          contDsc->content.push_back( cActor );

          delete aDsc;
          aDsc = nullptr;
        }
        contentNode = contentNode->next_sibling();
      }
    }
  }

  return contDsc;
}

PickableDescription *ActorParser::parsePickableDsc()
{
  PickableDescription* pickDsc = nullptr;

  if ( _xml != nullptr )
  {
    xml_node<>* pickableNode = _xml->first_node("Pickable");
    if (pickableNode)
    {
      pickDsc = new PickableDescription;

      pickDsc->stackable = getAttribute<bool>(pickableNode, "stackable");
      pickDsc->amount = getAttribute<int>(pickableNode, "amount");
      if ( pickDsc->amount == 0) pickDsc->amount = 1;

      // == effects == //
      xml_node<>* effectNode = pickableNode->first_node("Effect");
      if ( effectNode )
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

FighterDescription *ActorParser::parseFighterDsc()
{
  FighterDescription* fDsc = nullptr;

  if ( _xml != nullptr )
  {
    xml_node<>* fighterNode = _xml->first_node("Fighter");
    if (fighterNode)
    {
      fDsc = new FighterDescription;

      fDsc->power = getAttribute<float>(fighterNode, "power");
      fDsc->maxHp = getAttribute<float>(fighterNode, "maxHp");
    }
  }

  return fDsc;
}

AiDescription *ActorParser::parseAiDsc()
{
  AiDescription* aiDsc = nullptr;

  if ( _xml != nullptr )
  {
    xml_node<>* aiNode = _xml->first_node("Ai");
    if (aiNode)
    {
      aiDsc = new AiDescription;

      aiDsc->type = (AiType)getAttribute<int>(aiNode, "type");
    }
  }

  return aiDsc;
}

OpenableDescription *ActorParser::parseOpenableDsc()
{
  OpenableDescription* opDsc = nullptr;

  if ( _xml != nullptr )
  {
    xml_node<>* openableNode = _xml->first_node("Openable");
    if (openableNode)
    {
      opDsc = new OpenableDescription;

      opDsc->type = (OpenableType)getAttribute<int>(openableNode, "type");
      opDsc->lockId = getAttribute<int>(openableNode, "lockId");
      opDsc->locked = getAttribute<bool>(openableNode, "locked");
    }
  }

  return opDsc;
}

}
