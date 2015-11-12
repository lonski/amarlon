#include "character_serializer.h"
#include <xml_utils.h>
#include <character.h>
#include <utils.h>
#include <spell.h>
#include <spell_book.h>
#include <skill.h>
#include <race.h>
#include <character_class.h>

using namespace rapidxml;

namespace amarlon {

CharacterSerializer::CharacterSerializer()
  : CharacterSerializer(nullptr, nullptr)
{
}

CharacterSerializer::CharacterSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

CharacterSerializer::~CharacterSerializer()
{
}

void CharacterSerializer::serializeCharacterCommonPart(xml_node<>* characterNode, CharacterPtr character)
{
  if ( characterNode && character && _document )
  {
    addAttribute    ( characterNode, "level",        character->getLevel()            );
    addAttribute    ( characterNode, "hitPoints",    character->getHitPoints()        );
    addAttribute    ( characterNode, "maxHitPoints", character->getMaxHitPoints()     );
    addAttribute    ( characterNode, "experience",   character->getExperience()       );
    addAttribute    ( characterNode, "armorClass",   character->_defaultArmorClass    );
    addAttribute    ( characterNode, "speed",        character->_speed                );
    addAttributeEnum( characterNode, "class",        character->getClass()->getType() );
    addAttributeEnum( characterNode, "race",         character->getRace()->getType()  );
    addAttributeEnum( characterNode, "team",         character->getTeam()             );

    serializeSpellbook(characterNode, character);
    serializeSkills(character, characterNode);
    serializeModifiers(character, characterNode);

  }
}

void CharacterSerializer::serializeModifiers(CharacterPtr character, xml_node<>* characterNode)
{
  if ( !character->_modifiers.empty() )
  {
    xml_node<>* modifiersNode = _document->allocate_node(node_element, "Modifiers");
    characterNode->append_node(modifiersNode);
    for ( auto& mod : character->_modifiers )
    {
      xml_node<>* modNode = _document->allocate_node(node_element, "Mod");
      modifiersNode->append_node(modNode);
      addAttribute(modNode, "val", mod.toString() );
    }
  }
}

void CharacterSerializer::serializeSkills(CharacterPtr character, xml_node<>* characterNode)
{
  xml_node<>* skillsNode = _document->allocate_node(node_element, "Skills");
  characterNode->append_node(skillsNode);
  for ( auto s : character->_skills)
  {
    xml_node<>* skillNode = _document->allocate_node(node_element, "Skill");
    skillsNode->append_node(skillNode);
    addAttributeEnum(skillNode, "id", s->getId());
    addAttribute(skillNode, "level", s->getLevel());
  }
}

void CharacterSerializer::serializeSpellbook(xml_node<>* characterNode, CharacterPtr character)
{
  xml_node<>* spellbookNode = _document->allocate_node(node_element, "Spellbook");
  characterNode->append_node(spellbookNode);

  xml_node<>* slotsNode = _document->allocate_node(node_element, "Slots");
  spellbookNode->append_node(slotsNode);
  for ( auto slot : character->_spellbook->getSlots() )
  {
    xml_node<>* slotNode = _document->allocate_node(node_element, "Slot");
    slotsNode->append_node(slotNode);
    addAttribute(slotNode,"level",slot->level);
    addAttribute(slotNode,"prepared",(int)slot->isPrepared);
    if ( slot->spell ) addAttribute(slotNode,"spell",(int)slot->spell->getId());
  }

  xml_node<>* knownNode = _document->allocate_node(node_element, "Known");
  spellbookNode->append_node(knownNode);
  for ( auto spell : character->_spellbook->getKnownSpells() )
  {
    xml_node<>* spellNode = _document->allocate_node(node_element, "Spell");
    knownNode->append_node(spellNode);
    addAttribute(spellNode,"id",(int)spell->getId());
  }
}

}

