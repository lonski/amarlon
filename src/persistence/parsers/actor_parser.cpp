#include "actor_parser.h"
#include <utils/xml_utils.h>
#include <utils/utils.h>
#include <actor_descriptions.h>
#include <dialog_parser.h>
#include <ability_scores.h>

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

    if ( attributeExists(_xml, "id") )           actorDsc->id           = getAttribute<int>(_xml, "id");
    if ( attributeExists(_xml, "name") )         actorDsc->name         = getAttribute<std::string>(_xml, "name");
    if ( attributeExists(_xml, "inscription") )  actorDsc->inscription  = getAttribute<std::string>(_xml, "inscription");
    if ( attributeExists(_xml, "prototype") )    actorDsc->prototype    = getAttribute<int>(_xml, "prototype");
    if ( attributeExists(_xml, "x") )            actorDsc->x            = getAttribute<int>(_xml, "x");
    if ( attributeExists(_xml, "y") )            actorDsc->y            = getAttribute<int>(_xml, "y");
    if ( attributeExists(_xml, "blocks") )       actorDsc->blocks       = getAttribute<bool>(_xml, "blocks");
    if ( attributeExists(_xml, "visible") )      actorDsc->visible      = getAttribute<bool>(_xml, "visible");
    if ( attributeExists(_xml, "fovOnly") )      actorDsc->fovOnly      = getAttribute<bool>(_xml, "fovOnly");
    if ( attributeExists(_xml, "transparent") )  actorDsc->transparent  = getAttribute<bool>(_xml, "transparent");
    if ( attributeExists(_xml, "tilePriority") ) actorDsc->tilePriority = getAttribute<int>(_xml, "tilePriority");
    if ( attributeExists(_xml, "color") )        actorDsc->color        = getAttribute<std::string>(_xml, "color");

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

    enum
    {
      FT_NULL,
      AI,
      OPENABLE,
      WEARER,
      INVENTORY,
      CHARACTER,
      PICKABLE,
      DESTROYABLE,
      TRAP,
      TALKER,
      FT_END
    };

    //Parse Actor Features
    actorDsc->features[ PICKABLE    ] = parsePickableDsc();
    actorDsc->features[ CHARACTER   ] = parseCharacterDsc();
    actorDsc->features[ AI          ] = parseAiDsc();
    actorDsc->features[ OPENABLE    ] = parseOpenableDsc();
    actorDsc->features[ WEARER      ] = parseWearerDsc();
    actorDsc->features[ INVENTORY   ] = parseInventoryDsc();
    actorDsc->features[ DESTROYABLE ] = parseDestroyableDsc();
    actorDsc->features[ TRAP        ] = parseTrapDsc();
    actorDsc->features[ TALKER      ] = parseTalkerDsc();
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
      if ( attributeExists(invNode, "maxSize")) contDsc->maxSize = getAttribute<int>(invNode, "maxSize");
      ActorParser parser;
      xml_node<>* contentNode = invNode->first_node("Actor");
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
    xml_node<>* pickableNode = _xml->first_node("Scroll");
    if ( pickableNode )
    {
      ScrollDescriptionPtr sDsc( new ScrollDescription );
      if ( attributeExists( pickableNode, "spell") )
        sDsc->spellId = getAttribute<int>(pickableNode, "spell");
      pickDsc = sDsc;
    }
    else
    {
      pickableNode = _xml->first_node("Pickable");
      if ( pickableNode ) pickDsc.reset( new PickableDescription );
    }

    if (pickableNode != nullptr)
    {
      if ( attributeExists( pickableNode, "scriptId") )   pickDsc->scriptId = getAttribute<int>(pickableNode, "scriptId");
      if ( attributeExists( pickableNode, "stackable") )  pickDsc->stackable = getAttribute<bool>(pickableNode, "stackable");
      if ( attributeExists( pickableNode, "amount") )     pickDsc->amount = getAttribute<int>(pickableNode, "amount");
      if ( attributeExists( pickableNode, "itemSlot") )   pickDsc->itemSlot = getAttribute<int>(pickableNode, "itemSlot");
      if ( attributeExists( pickableNode, "armorClass") ) pickDsc->armorClass = getAttribute<int>(pickableNode, "armorClass");
      if ( attributeExists( pickableNode, "weight") )     pickDsc->weight = getAttribute<int>(pickableNode, "weight");
      if ( attributeExists( pickableNode, "price") )      pickDsc->price = getAttribute<int>(pickableNode, "price");
      if ( attributeExists( pickableNode, "uses") )       pickDsc->uses = getAttribute<int>(pickableNode, "uses");
      if ( attributeExists( pickableNode, "range") )      pickDsc->range = getAttribute<int>(pickableNode, "range");
      if ( attributeExists( pickableNode, "radius") )     pickDsc->radius = getAttribute<int>(pickableNode, "radius");
      if ( attributeExists( pickableNode, "targetType") ) pickDsc->targetType = getAttribute<int>(pickableNode, "targetType");
      if ( attributeExists( pickableNode, "damage") )     pickDsc->damage = getAttribute<std::string>(pickableNode, "damage");
      if ( attributeExists( pickableNode, "armorType") )     pickDsc->armorType = getAttribute<int>(pickableNode, "armorType");
      if ( attributeExists( pickableNode, "weaponType") )    pickDsc->weaponType = getAttribute<int>(pickableNode, "weaponType");
      if ( attributeExists( pickableNode, "amunitionType") ) pickDsc->amunitionType = getAttribute<int>(pickableNode, "amunitionType");
      if ( attributeExists( pickableNode, "category") )      pickDsc->category = getAttribute<int>(pickableNode, "category");
      if ( attributeExists( pickableNode, "weaponSize") )    pickDsc->weaponSize = getAttribute<int>(pickableNode, "weaponSize");
    }
  }

  return pickDsc;
}

CharacterDescriptionPtr ActorParser::parseCharacterDsc()
{
  CharacterDescriptionPtr dsc;

  if ( _xml != nullptr )
  {
    //character parsing
    xml_node<>* characterNode = _xml->first_node("Character");
    if ( characterNode != nullptr )
    {
      dsc.reset( new CharacterDescription );
      dsc->type = 1;//CharacterType::Generic
    }
    else
    {
      //playable character parsing
      characterNode = _xml->first_node("PlayableCharacter");
      if (characterNode != nullptr)
      {
        dsc.reset( new CharacterDescription );
        dsc->type = 2; //CharacterType::PlayableCharacter;
      }
    }

    if ( dsc && characterNode )
    {
      if ( attributeExists(characterNode, "level") )        dsc->level = getAttribute<int>(characterNode, "level");
      if ( attributeExists(characterNode, "hitPoints") )    dsc->hitPoints = getAttribute<int>(characterNode, "hitPoints");
      if ( attributeExists(characterNode, "maxHitPoints") ) dsc->maxHitPoints = getAttribute<int>(characterNode, "maxHitPoints");
      if ( attributeExists(characterNode, "armorClass") )   dsc->defaultArmorClass = getAttribute<int>(characterNode, "armorClass");
      if ( attributeExists(characterNode, "class") )        dsc->cClass = getAttribute<int>(characterNode, "class");
      if ( attributeExists(characterNode, "race") )         dsc->race = getAttribute<int>(characterNode, "race");
      if ( attributeExists(characterNode, "experience") )   dsc->experience = getAttribute<int>(characterNode, "experience");
      if ( attributeExists(characterNode, "speed") )        dsc->speed = getAttribute<int>(characterNode, "speed");
      if ( attributeExists(characterNode, "team") )         dsc->team = getAttribute<int>(characterNode, "team");
      if ( attributeExists(characterNode, "morale") )       dsc->morale = getAttribute<int>(characterNode, "morale");
      if ( attributeExists(characterNode, "damage") )       dsc->damage = getAttribute<std::string>(characterNode, "damage");

      //Parse Spellbook
      xml_node<>* spellbookNode = characterNode->first_node("Spellbook");
      if ( spellbookNode )
      {
        SpellbookDescription spellbook;
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
            spellbook.spellSlots.push_back(slot);
            slotNode = slotNode->next_sibling();
          }
        }
        xml_node<>* knownNode = spellbookNode->first_node("Known");
        if ( knownNode )
        {
          xml_node<>* kNode = knownNode->first_node("Spell");
          while( kNode )
          {
            spellbook.knownSpells.push_back( getAttribute<int>(kNode, "id") );
            kNode = kNode->next_sibling();
          }
        }

        dsc->spellbook = spellbook;
      }

      //Parse skills
      xml_node<>* skillsNode = characterNode->first_node("Skills");
      if ( skillsNode )
      {
        xml_node<>* skillNode = skillsNode->first_node("Skill");
        while( skillNode )
        {
          std::pair<int, int> s;
          s.first = getAttribute<int>(skillNode, "id");
          s.second = getAttribute<int>(skillNode, "level");
          dsc->skills.push_back(s);
          skillNode = skillNode->next_sibling();
        }
      }

      //Parse modifiers
      xml_node<>* modsNode = characterNode->first_node("Modifiers");
      if ( modsNode )
      {
        xml_node<>* modNode = modsNode->first_node("Mod");
        while( modNode )
        {
          if ( attributeExists(modNode, "val") )
          {
            dsc->modifiers.push_back( getAttribute<std::string>(modNode, "val") );
          }
          modNode = modNode->next_sibling();
        }
      }

      //Parse AbilitzScores
      xml_node<>* attrNode = characterNode->first_node("AbilityScores");
      if ( attrNode != nullptr)
      {
        for ( AbilityScore::Type as : AbilityScore::Type() )
        {
          if ( attributeExists(attrNode, AbilityScore::toStr(as)))
          {
            dsc->abilityScores[ (int)as ] = getAttribute<int>(attrNode, AbilityScore::toStr(as));
          }
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
    xml_node<>* aiNode = _xml->first_node("Ai");
    if (aiNode != nullptr)
    {
      aiDsc.reset( new AiDescription );
      aiDsc->type = 1; //generic ai
    }
    else if ( (aiNode = _xml->first_node("PlayerAi")) )
    {
      aiDsc.reset( new AiDescription );
      aiDsc->type = 2; //player ai
    }

    if ( aiNode )
    {
      if (attributeExists(aiNode, "script") ) aiDsc->script = getAttribute<int>(aiNode, "script");
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
      if (attributeExists(openableNode,"lockId"))    opDsc->lockId = getAttribute<int>(openableNode, "lockId");
      if (attributeExists(openableNode,"locked"))    opDsc->locked = getAttribute<bool>(openableNode, "locked");
      if (attributeExists(openableNode,"lockLevel")) opDsc->lockLevel = getAttribute<int>(openableNode, "lockLevel");
      if (attributeExists(openableNode,"scriptId"))  opDsc->scriptId = getAttribute<int>(openableNode, "scriptId");
      if (attributeExists(openableNode,"closed"))    opDsc->closed = getAttribute<bool>(openableNode, "closed");

      xml_node<>* openedNode = openableNode->first_node("StateOpened");
      if ( openedNode )
      {
        OpenableState s;
        s.blocks = getAttribute<bool>(openedNode, "blocks");
        s.transparent = getAttribute<bool>(openedNode, "transparent");

        std::string charStr = getAttribute<std::string>(openedNode, "character");
        if (charStr.size() > 1 || std::isdigit(charStr[0]))
          s.symbol = (unsigned char)std::stol(charStr);
        else
          s.symbol = charStr[0];

        opDsc->openedState = s;
      }

      xml_node<>* closedNode = openableNode->first_node("StateClosed");
      if ( closedNode )
      {
        OpenableState s;
        s.blocks = getAttribute<bool>(closedNode, "blocks");
        s.transparent = getAttribute<bool>(closedNode, "transparent");

        std::string charStr = getAttribute<std::string>(closedNode, "character");
        if (charStr.size() > 1 || std::isdigit(charStr[0]))
          s.symbol = (unsigned char)std::stol(charStr);
        else
          s.symbol = charStr[0];

        opDsc->closedState = s;
      }
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
        int slot = getAttribute<int>(itemSlotNode, "type");
        wrDsc->itemSlots.push_back(slot);
        itemSlotNode = itemSlotNode->next_sibling();
      }

      xml_node<>* equippedNode = wearerNode->first_node("Actor");
      while (equippedNode != nullptr)
      {
        parser.setSource(equippedNode);
        wrDsc->eqItems.push_back(parser.parseDescription());
        equippedNode = equippedNode->next_sibling();
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

        rule.dropActorId = getAttribute<int>(dropRuleNode, "dropActorId");
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
      if ( attributeExists(trapNode,"armed") )      tDsc->armed = getAttribute<bool>( trapNode, "armed" );
      if ( attributeExists(trapNode,"detected") )   tDsc->detected = getAttribute<bool>( trapNode, "detected" );
      if ( attributeExists(trapNode,"difficulty") ) tDsc->difficulty = getAttribute<int>( trapNode, "difficulty" );
      if ( attributeExists(trapNode,"id") )         tDsc->id = getAttribute<int>( trapNode, "id" );
    }
  }

  return tDsc;
}

TalkerDescriptionPtr ActorParser::parseTalkerDsc()
{
  TalkerDescriptionPtr tDsc;

  if (_xml != nullptr)
  {
    xml_node<>* tNode = _xml->first_node("Talker");
    if (tNode != nullptr)
    {
      tDsc.reset( new TalkerDescription );
      if ( attributeExists(tNode,"id") ) tDsc->id = getAttribute<int>( tNode, "id" );

      DialogParser parser;
      tDsc->dialogs = parser.parse( *tDsc->id );
    }
  }

  return tDsc;
}

}

