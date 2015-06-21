#include "monster_serializer.h"
#include <utils.h>
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

    _mobNode->append_attribute( _document->allocate_attribute(
                                       "hitPointsBonus",
                                       _document->allocate_string( toStr( mob->_hpMod ).c_str()) ) );
    _mobNode->append_attribute( _document->allocate_attribute(
                                       "morale",
                                       _document->allocate_string( toStr( mob->getMorale() ).c_str()) ) );
    _mobNode->append_attribute( _document->allocate_attribute(
                                       "damageDice",
                                       _document->allocate_string(
                                          ( toStr(mob->_damageDiceCount)
                                            +"d"
                                            +toStr(static_cast<int>(mob->_damageDice))
                                          ).c_str()) ) );

    CharacterSerializer::serializeCharacterCommonPart(_mobNode, mob);
  }
  return mob != nullptr;
}

}
