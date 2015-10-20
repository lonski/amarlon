#include "actor_parser.h"
#include <utils/xml_utils.h>
#include <utils/utils.h>
#include <actor_descriptions.h>

namespace amarlon {

using namespace rapidxml;
using namespace std;

ActorParser::ActorParser()
{
}

ActorParser::ActorParser(xml_node<> *xmlNode)
 : Parser(xmlNode)
{
}

ActorDescriptionPtr ActorParser::parseDescription()
{
  ActorDescriptionPtr actorDsc;

  if ( _xml != nullptr )
  {
    actorDsc.reset( new ActorDescription );

    actorDsc->id = (ActorType)getAttribute<int>(_xml, "id");

    if ( attributeExists(_xml, "name") )         actorDsc->name         = getAttribute<std::string>(_xml, "name");
    if ( attributeExists(_xml, "x") )            actorDsc->x            = getAttribute<int>(_xml, "x");
    if ( attributeExists(_xml, "y") )            actorDsc->y            = getAttribute<int>(_xml, "y");
    if ( attributeExists(_xml, "blocks") )       actorDsc->blocks       = getAttribute<bool>(_xml, "blocks");
    if ( attributeExists(_xml, "visible") )      actorDsc->visible      = getAttribute<bool>(_xml, "visible");
    if ( attributeExists(_xml, "fovOnly") )      actorDsc->fovOnly      = getAttribute<bool>(_xml, "fovOnly");
    if ( attributeExists(_xml, "transparent") )  actorDsc->transparent  = getAttribute<bool>(_xml, "transparent");
    if ( attributeExists(_xml, "tilePriority") ) actorDsc->tilePriority = getAttribute<int>(_xml, "tilePriority");
    if ( attributeExists(_xml, "color") )        actorDsc->color        = strToColor( getAttribute<std::string>(_xml, "color") );

    if ( xml_node<>* dNode = _xml->first_node("Description") ) actorDsc->description = getNodeValue<std::string>(dNode);

    if ( attributeExists(_xml, "character") )
    {
      std::string charStr = getAttribute<std::string>(_xml, "character");
      if (charStr.size() > 1 || std::isdigit(charStr[0]))
        actorDsc->symbol = (unsigned char)std::stol(charStr);
      else
        actorDsc->symbol = charStr[0];
    }

    //Parse Status Effects
    xml_node<>* semNode = _xml->first_node("StatusEffects");
    if ( semNode )
    {
      xml_node<>* eNode = semNode->first_node("StatusEffect");
      while ( eNode )
      {
        StatusEffectDsc d;
        d.duration = getAttribute<int>(eNode, "duration");
        d.name = getAttribute<std::string>(eNode, "name");
        d.script = getAttribute<std::string>(eNode, "script");
        actorDsc->statusEffects.push_back( d );
        eNode = eNode->next_sibling();
      }
    }

    //Parse Actor Features
    actorDsc->pickable = parsePickableDsc();
    actorDsc->character = parseCharacterDsc();
    actorDsc->ai = parseAiDsc();
    actorDsc->openable = parseOpenableDsc();
    actorDsc->wearer = parseWearerDsc();
    actorDsc->inventory = parseInventoryDsc();
    actorDsc->destroyable = parseDestroyableDsc();
    actorDsc->trap = parseTrapDsc();
  }

  return actorDsc;
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
      ActorParser parser;
      xml_node<>* contentNode = invNode->first_node("Content");
      while ( contentNode != nullptr)
      {
        parser.setSource(contentNode);
        contDsc->content.push_back( parser.parseDescription() );
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

      pickDsc->scriptId = getAttribute<int>(pickableNode, "scriptId");
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

      //Parse Spellbook
      xml_node<>* spellbookNode = characterNode->first_node("Spellbook");
      if ( spellbookNode )
      {
        xml_node<>* slotsNode = spellbookNode->first_node("Slots");
        if ( slotsNode )
        {
          xml_node<>* slotNode = slotsNode->first_node("Slot");
          while ( slotNode )
          {
            SpellSlotDescription slot;
            slot.level = getAttribute<int>(slotNode, "level");
            slot.prepared = getAttribute<bool>(slotNode, "prepared");
            slot.spell = getAttribute<int>(slotNode, "spell");
            dsc->spellbook.spellSlots.push_back(slot);
            slotNode = slotNode->next_sibling();
          }
        }
        xml_node<>* knownNode = spellbookNode->first_node("Known");
        if ( knownNode )
        {
          xml_node<>* kNode = knownNode->first_node("Spell");
          while( kNode )
          {
            dsc->spellbook.knownSpells.push_back( getAttribute<int>(kNode, "id") );
            kNode = kNode->next_sibling();
          }
        }
      }

      //Parse skills
      xml_node<>* skillsNode = characterNode->first_node("Skills");
      if ( skillsNode )
      {
        xml_node<>* skillNode = skillsNode->first_node("Skill");
        while( skillNode )
        {
          SkillDescription s;
          s.id = getAttribute<int>(skillNode, "id");
          s.level = getAttribute<int>(skillNode, "level");
          dsc->skills.push_back(s);
          skillNode = skillNode->next_sibling();
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
      aiDsc.reset( new AiDescription );
      aiDsc->type = AiType::MonsterAi;
    }
    else
    {
      xml_node<>* pAiNode = _xml->first_node("PlayerAi");
      if (pAiNode != nullptr)
      {
        aiDsc.reset( new AiDescription );
        aiDsc->type = AiType::PlayerAi;
      }
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
    if ( openableNode )
    {
      opDsc.reset( new OpenableDescription );
      opDsc->lockId = getAttribute<int>(openableNode, "lockId");
      opDsc->locked = getAttribute<bool>(openableNode, "locked");
      opDsc->lockLevel = getAttribute<int>(openableNode, "lockLevel");
      opDsc->scriptId = getAttribute<int>(openableNode, "scriptId");
      opDsc->closed = getAttribute<bool>(openableNode, "closed");
    }
  }

  return opDsc;
}

WearerDescriptionPtr ActorParser::parseWearerDsc()
{
  WearerDescriptionPtr wrDsc;

  if (_xml != nullptr)
  {
    ActorParser parser;
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
          parser.setSource(equippedNode);
          wrDsc->eqItems.push_back(parser.parseDescription());
        }

        itemSlotNode = itemSlotNode->next_sibling();
      }
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

TrapDescriptionPtr ActorParser::parseTrapDsc()
{
  TrapDescriptionPtr tDsc;

  if (_xml != nullptr)
  {
    xml_node<>* trapNode = _xml->first_node("Trap");
    if (trapNode != nullptr)
    {
      tDsc.reset( new TrapDescription );
      tDsc->armed = getAttribute<bool>( trapNode, "armed" );
      tDsc->detected = getAttribute<bool>( trapNode, "detected" );
      tDsc->difficulty = getAttribute<int>( trapNode, "difficulty" );
      tDsc->id = getAttribute<int>( trapNode, "id" );
    }
  }

  return tDsc;
}

}

