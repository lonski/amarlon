#include "character_serializer.h"
#include <xml_utils.h>
#include <character.h>
#include <utils.h>
#include <spell.h>

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
    addAttribute    ( characterNode, "level",        character->getLevel()           );
    addAttribute    ( characterNode, "hitPoints",    character->getHitPoints()       );
    addAttribute    ( characterNode, "maxHitPoints", character->getMaxHitPoints()    );
    addAttribute    ( characterNode, "experience",   character->getExperience()      );
    addAttribute    ( characterNode, "armorClass",   character->_defaultArmorClass   );
    addAttribute    ( characterNode, "speed",        character->_speed               );
    addAttributeEnum( characterNode, "class",        character->getClass()           );
    addAttributeEnum( characterNode, "race",         character->getRace()            );

    xml_node<>* spellsNode = _document->allocate_node(node_element, "Spells");
    characterNode->append_node(spellsNode);
    for ( auto spell : character->getSpells() )
    {
      xml_node<>* spellNode = _document->allocate_node(node_element, "Spell");
      spellsNode->append_node(spellNode);
      addAttributeEnum(spellNode, "id", spell->getId() );
    }
  }
}

}
