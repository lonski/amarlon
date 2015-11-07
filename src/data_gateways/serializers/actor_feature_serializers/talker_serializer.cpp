#include "talker_serializer.h"
#include <talker.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

TalkerSerializer::TalkerSerializer()
  : TalkerSerializer(nullptr, nullptr)
{
}

TalkerSerializer::TalkerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

TalkerSerializer::~TalkerSerializer()
{
}

bool TalkerSerializer::serialize(ActorFeaturePtr af)
{
  TalkerPtr talker = std::dynamic_pointer_cast<Talker>(af);
  if ( talker && _xml && _document )
  {
    xml_node<>* tNode = _document->allocate_node(node_element, "Talker");
    _xml->append_node( tNode );

    addAttribute( tNode, "id", talker->getId() );
    return true;
  }
  return false;
}

}
