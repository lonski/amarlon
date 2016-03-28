#include "talker_serializer.h"
#include <talker_description.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

TalkerSerializer::TalkerSerializer()
  : TalkerSerializer(nullptr, nullptr)
{
}

TalkerSerializer::TalkerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
}

TalkerSerializer::~TalkerSerializer()
{
}

bool TalkerSerializer::serialize(DescriptionPtr dsc)
{
  TalkerDescriptionPtr tDsc = std::dynamic_pointer_cast<TalkerDescription>(dsc);
  if ( tDsc && _xml && _document && tDsc->id )
  {
    xml_node<>* tNode = _document->allocate_node(node_element, "Talker");
    _xml->append_node( tNode );

    addAttribute( tNode, "id", *tDsc->id );
    return true;
  }
  return false;
}

}
