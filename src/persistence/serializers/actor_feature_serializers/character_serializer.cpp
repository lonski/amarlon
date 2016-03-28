#include "character_serializer.h"
#include <xml_utils.h>
#include <character_description.h>

using namespace rapidxml;

namespace amarlon {

CharacterSerializer::CharacterSerializer()
  : CharacterSerializer(nullptr, nullptr)
{
}

CharacterSerializer::CharacterSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
}

CharacterSerializer::~CharacterSerializer()
{
}

bool CharacterSerializer::serialize(DescriptionPtr dsc)
{
  bool serialized = false;
  CharacterDescriptionPtr cDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);
  if ( cDsc )
  {
    xml_node<>* cNode = nullptr;

    if ( cDsc->type && cDsc->type == 2 )
    {
      cNode = _document->allocate_node(node_element, "PlayableCharacter");
    }
    else
    {
      cNode = _document->allocate_node(node_element, "Character");
    }
    _xml->append_node( cNode );

    if ( cDsc->level )             addAttribute( cNode, "level",        *cDsc->level             );
    if ( cDsc->hitPoints )         addAttribute( cNode, "hitPoints",    *cDsc->hitPoints         );
    if ( cDsc->maxHitPoints )      addAttribute( cNode, "maxHitPoints", *cDsc->maxHitPoints      );
    if ( cDsc->defaultArmorClass ) addAttribute( cNode, "experience",   *cDsc->defaultArmorClass );
    if ( cDsc->speed )             addAttribute( cNode, "speed",        *cDsc->speed             );
    if ( cDsc->damage )            addAttribute( cNode, "damage",       *cDsc->damage            );
    if ( cDsc->cClass )            addAttribute( cNode, "class",        *cDsc->cClass            );
    if ( cDsc->race )              addAttribute( cNode, "race",         *cDsc->race              );
    if ( cDsc->team )              addAttribute( cNode, "team",         *cDsc->team              );
    if ( cDsc->morale )            addAttribute( cNode, "morale",       *cDsc->morale            );

    serializeAbilityScores(cDsc, cNode);
    serializeModifiers(cDsc, cNode);
    serializeSkills(cDsc, cNode);
    serializeSpellbook(cDsc, cNode);

    serialized = true;
  }
  return serialized;
}

void CharacterSerializer::serializeAbilityScores(CharacterDescriptionPtr dsc, rapidxml::xml_node<>* characterNode)
{
  xml_node<>* _asNode = _document->allocate_node(node_element, "AbilityScores");
  characterNode->append_node( _asNode );

  static std::vector< std::string > asString
  {
    "STR",
    "INT",
    "WIS",
    "DEX",
    "CON",
    "CHA"
  };

  for ( auto& kv : dsc->abilityScores )
  {
    addAttribute( _asNode, asString[kv.first], kv.second );
  }
}

void CharacterSerializer::serializeModifiers(CharacterDescriptionPtr dsc, xml_node<>* characterNode)
{
  if ( !dsc->modifiers.empty() )
  {
    xml_node<>* modifiersNode = _document->allocate_node(node_element, "Modifiers");
    characterNode->append_node(modifiersNode);
    for ( auto& mod : dsc->modifiers )
    {
      xml_node<>* modNode = _document->allocate_node(node_element, "Mod");
      modifiersNode->append_node(modNode);
      addAttribute(modNode, "val", mod );
    }
  }
}

void CharacterSerializer::serializeSkills(CharacterDescriptionPtr dsc, xml_node<>* characterNode)
{
  xml_node<>* skillsNode = _document->allocate_node(node_element, "Skills");
  characterNode->append_node(skillsNode);

  for ( auto s : dsc->skills)
  {
    xml_node<>* skillNode = _document->allocate_node(node_element, "Skill");
    skillsNode->append_node(skillNode);
    addAttribute(skillNode, "id", s.first);
    addAttribute(skillNode, "level", s.second);
  }
}

void CharacterSerializer::serializeSpellbook(CharacterDescriptionPtr dsc, xml_node<>* characterNode)
{
  if ( dsc->spellbook )
  {
    xml_node<>* spellbookNode = _document->allocate_node(node_element, "Spellbook");
    characterNode->append_node(spellbookNode);

    xml_node<>* slotsNode = _document->allocate_node(node_element, "Slots");
    spellbookNode->append_node(slotsNode);
    for ( auto slot : (*dsc->spellbook).spellSlots )
    {
      xml_node<>* slotNode = _document->allocate_node(node_element, "Slot");
      slotsNode->append_node(slotNode);
      addAttribute(slotNode,"level",slot.level);
      addAttribute(slotNode,"prepared",(int)slot.prepared);
      if ( slot.spell > 0 ) addAttribute(slotNode,"spell",slot.spell);
    }

    xml_node<>* knownNode = _document->allocate_node(node_element, "Known");
    spellbookNode->append_node(knownNode);
    for ( auto ks : (*dsc->spellbook).knownSpells )
    {
      xml_node<>* spellNode = _document->allocate_node(node_element, "Spell");
      knownNode->append_node(spellNode);
      addAttribute(spellNode,"id",ks);
    }
  }
}

}

