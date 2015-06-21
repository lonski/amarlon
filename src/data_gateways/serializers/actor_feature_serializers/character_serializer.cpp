#include "character_serializer.h"
#include <character.h>
#include <utils.h>

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
    characterNode->append_attribute( _document->allocate_attribute(
                                       "level",
                                       _document->allocate_string( toStr( character->getLevel() ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "hitPoints",
                                       _document->allocate_string( toStr( character->getHitPoints() ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "maxHitPoints",
                                       _document->allocate_string( toStr( character->getMaxHitPoints() ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "experience",
                                       _document->allocate_string( toStr( character->getExperience() ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "armorClass",
                                       _document->allocate_string( toStr( character->_defaultArmorClass ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "speed",
                                       _document->allocate_string( toStr( character->_speed ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "class",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(character->getClass())
                                                                     ).c_str()) ) );
    characterNode->append_attribute( _document->allocate_attribute(
                                       "race",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(character->getRace())
                                                                     ).c_str()) ) );
  }
}

}
