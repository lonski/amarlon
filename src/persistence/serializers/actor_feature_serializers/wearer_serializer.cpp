#include "wearer_serializer.h"
#include <wearer_description.h>
#include <actor_descriptions.h>
#include <actor_serializer.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

WearerSerializer::WearerSerializer()
  : WearerSerializer(nullptr, nullptr)  
{
}

WearerSerializer::WearerSerializer(xml_document<> *document, xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

WearerSerializer::~WearerSerializer()
{
}

bool WearerSerializer::serialize(DescriptionPtr dsc)
{
  WearerDescriptionPtr wDsc = std::dynamic_pointer_cast<WearerDescription>(dsc);
  if ( wDsc && _document && _xml )
  {
    xml_node<>* wearerNode = _document->allocate_node(node_element, "Wearer");
    _xml->append_node( wearerNode );

    for ( auto slot : wDsc->itemSlots )
    {
      xml_node<>* slotNode = _document->allocate_node(node_element, "ItemSlot");
      wearerNode->append_node( slotNode );
      addAttribute( slotNode, "type", slot );
    }

    ActorSerializer actorSerializer(_document, wearerNode);
    for ( auto a : wDsc->eqItems )
    {
      actorSerializer.serialize( a );
    }
  }

  return wDsc != nullptr;
}

}

