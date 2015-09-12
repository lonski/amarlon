#include "actor_parser.h"
#include <string>
#include <utils/xml_utils.h>
#include <utils/utils.h>
#include <races.h>

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
  _featureParsers[ActorFeature::INVENTORY]   = [&](){ return parseInventoryDsc(); };
  _featureParsers[ActorFeature::OPENABLE]    = [&](){ return parseOpenableDsc(); };
  _featureParsers[ActorFeature::PICKABLE]    = [&](){ return parsePickableDsc(); };
  _featureParsers[ActorFeature::CHARACTER]   = [&](){ return parseCharacterDsc(); };
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

    xml_node<>* dNode = _xml->first_node("Description");
    if ( dNode != nullptr )
    {
      actorDsc->description = getNodeValue<std::string>(dNode);
    }

  }

  return actorDsc;
}

void ActorParser::parseInventoryContentNode(InventoryDescriptionPtr contDsc, xml_node<>* contentNode)
{
  ActorParser aParser(contentNode);
  InventoryDescription::Content cActor;
  ActorDescriptionPtr aDsc = aParser.parseActorDsc();
  if (aDsc != nullptr)
  {
    cActor.actorType = aDsc->id;

    cActor.container = aParser.parseInventoryDsc() ;
    cActor.openable = aParser.parseOpenableDsc();
    cActor.pickable = aParser.parsePickableDsc();
    cActor.character = aParser.parseCharacterDsc();
    cActor.ai = aParser.parseAiDsc();
    cActor.destroyable = aParser.parseDestroyableDsc();

    contDsc->content.push_back( cActor );
  }
}

InventoryDescriptionPtr ActorParser::parseInventoryDsc()
{
  InventoryDescriptionPtr contDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* invNode = _xml->first_node("Inventory");
    if ( invNode != nullptr)
    {
      contDsc.reset( new InventoryDescription );

      contDsc->maxSize = getAttribute<int>(invNode, "maxSize");

      xml_node<>* contentNode = invNode->first_node("Content");

      while ( contentNode != nullptr)
      {
        parseInventoryContentNode(contDsc, contentNode);
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
      pickDsc->armorClass = getAttribute<int>(pickableNode, "armorClass");
      pickDsc->weight = getAttribute<int>(pickableNode, "weight");
      pickDsc->price = getAttribute<int>(pickableNode, "price");
      pickDsc->uses = getAttribute<int>(pickableNode, "uses");
      pickDsc->targetType = (TargetType)getAttribute<int>(pickableNode, "targetType");

      pickDsc->damage = Damage( getAttribute<std::string>(pickableNode, "damage") );

      // == effects == //
      xml_node<>* effectNode = pickableNode->first_node("Effect");
      if ( effectNode != nullptr)
      {
        _effectParser.setSource( effectNode );
        pickDsc->effect = _effectParser.parseEffectDsc();
      }
    }
  }

  return pickDsc;
}

CharacterDescriptionPtr ActorParser::parseCharacterDsc()
{
  CharacterDescriptionPtr dsc;

  if ( _xml != nullptr )
  {
    //playable character parsing
    xml_node<>* characterNode = _xml->first_node("PlayableCharacter");
    if (characterNode != nullptr)
    {
      PlayableCharacterDescriptionPtr pdsc( new PlayableCharacterDescription );

      xml_node<>* attrNode = characterNode->first_node("AbilityScores");
      if ( attrNode != nullptr)
      {
        for ( AbilityScore::Type as : AbilityScore::Type() )
        {
          pdsc->abilityScores[as] = getAttribute<int>(attrNode, AbilityScore::toStr(as));
        }
      }

      dsc = pdsc;
    }
    else
    {
      //monster character parsing
      characterNode = _xml->first_node("Monster");
      if ( characterNode != nullptr )
      {
        MonsterDescriptionPtr mdsc( new MonsterDescription );

        mdsc->hitPointsBonus = getAttribute<int>(characterNode, "hitPointsBonus");
        mdsc->morale = getAttribute<int>(characterNode, "morale");
        mdsc->damage = Damage( getAttribute<std::string>(characterNode, "damage") );

        dsc = mdsc;
      }
    }

    if ( dsc && characterNode )
    {
      dsc->level = getAttribute<int>(characterNode, "level");
      dsc->hitPoints = getAttribute<int>(characterNode, "hitPoints");
      dsc->maxHitPoints = getAttribute<int>(characterNode, "maxHitPoints");
      dsc->defaultArmorClass = getAttribute<int>(characterNode, "armorClass");
      dsc->cClass = (CharacterClass)getAttribute<int>(characterNode, "class");
      dsc->race = (Race)getAttribute<int>(characterNode, "race");
      dsc->experience = getAttribute<int>(characterNode, "experience");
      dsc->speed = getAttribute<int>(characterNode, "speed");

      xml_node<>* spellsNode = characterNode->first_node("Spells");
      if ( spellsNode )
      {
        xml_node<>* spellNode = spellsNode->first_node("Spell");
        while ( spellNode )
        {
          dsc->spells.insert(static_cast<SpellId>(getAttribute<int>(spellNode, "id")));
          spellNode = spellNode->next_sibling();
        }
      }
    }

  }

  return dsc;
}

AiDescriptionPtr ActorParser::parseAiDsc()
{
  AiDescriptionPtr aiDsc;

  if ( _xml != nullptr )
  {
    xml_node<>* mobAiNode = _xml->first_node("MonsterAi");
    if (mobAiNode != nullptr)
    {
      MonsterAiDescriptionPtr mobAiDsc = std::make_shared<MonsterAiDescription>();
      aiDsc = mobAiDsc;
    }
  }

  return aiDsc;
}

OpenableDescriptionPtr ActorParser::parseOpenableDsc()
{
  OpenableDescriptionPtr opDsc;

  if ( _xml != nullptr )
  {
    //door
    xml_node<>* openableNode = _xml->first_node("OpenableDoor");
    if (openableNode != nullptr)
    {
      opDsc = std::make_shared<OpenableDoorDescription>();
    }
    else
    //container
    {
      openableNode = _xml->first_node("OpenableContainer");
      if ( openableNode != nullptr )
      {
        opDsc = std::make_shared<OpenableContaineryDescription>();
      }
    }

    //create common dsc
    if ( opDsc != nullptr )
    {
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
          parseInventoryContentNode(wrDsc->eqItems, equippedNode );
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
