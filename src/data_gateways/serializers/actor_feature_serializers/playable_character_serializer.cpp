#include "playable_character_serializer.h"
#include <utils.h>
#include <xml_utils.h>
#include <playable_character.h>

using namespace rapidxml;

namespace amarlon {

PlayableCharacterSerializer::PlayableCharacterSerializer()
  : PlayableCharacterSerializer(nullptr, nullptr)
{
}

PlayableCharacterSerializer::PlayableCharacterSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : CharacterSerializer(document, xmlNode)
{
}

PlayableCharacterSerializer::~PlayableCharacterSerializer()
{
}

bool PlayableCharacterSerializer::serialize(ActorFeaturePtr af)
{
  PlayableCharacterPtr pc = std::dynamic_pointer_cast<PlayableCharacter>(af);
  if ( pc && _document && _xml )
  {
    xml_node<>* _pcNode = _document->allocate_node(node_element, "PlayableCharacter");
    _xml->append_node( _pcNode );

    xml_node<>* _asNode = _document->allocate_node(node_element, "AbilityScores");
    _pcNode->append_node( _asNode );

    for ( AbilityScore::Type as : AbilityScore::Type() )
    {
      addAttribute( _asNode, AbilityScore::toStr(as), pc->getAbilityScore(as) );
    }

    CharacterSerializer::serializeCharacterCommonPart(_pcNode, pc);
  }
  return pc != nullptr;
}

}

