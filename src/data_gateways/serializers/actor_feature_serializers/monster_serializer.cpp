#include "monster_serializer.h"
#include <utils.h>
#include <xml_utils.h>
#include <monster.h>

using namespace rapidxml;

namespace amarlon {

MonsterSerializer::MonsterSerializer()
  : MonsterSerializer(nullptr, nullptr)
{
}

MonsterSerializer::MonsterSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : CharacterSerializer(document, xmlNode)
{
}

MonsterSerializer::~MonsterSerializer()
{
}

bool MonsterSerializer::serialize(ActorFeaturePtr af)
{
  MonsterPtr mob = std::dynamic_pointer_cast<Monster>(af);
  if ( mob && _document && _xml )
  {
    xml_node<>* _mobNode = _document->allocate_node(node_element, "Monster");
    _xml->append_node( _mobNode );

    addAttribute( _mobNode, "hitPointsBonus", mob->_hpMod );
    addAttribute( _mobNode, "morale", mob->getMorale() );
    addAttribute( _mobNode, "damage", std::string(mob->_damage) );

    CharacterSerializer::serializeCharacterCommonPart(_mobNode, mob);
  }
  return mob != nullptr;
}

}

