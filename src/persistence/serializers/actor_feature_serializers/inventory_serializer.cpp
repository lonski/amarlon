#include "inventory_serializer.h"
#include <inventory.h>
#include <utils.h>
#include <xml_utils.h>
#include <inventory_description.h>
#include <actor_serializer.h>
#include <actor_descriptions.h>

using namespace rapidxml;

namespace amarlon {

InventorySerializer::InventorySerializer()
  : InventorySerializer(nullptr, nullptr)
{
}

InventorySerializer::InventorySerializer(xml_document<> *document, xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

InventorySerializer::~InventorySerializer()
{
}

bool InventorySerializer::serialize(DescriptionPtr dsc)
{
  InventoryDescriptionPtr iDsc = std::dynamic_pointer_cast<InventoryDescription>(dsc);
  if ( iDsc && _document && _xml )
  {
    xml_node<>* _containerNode = _document->allocate_node(node_element, "Inventory");
    _xml->append_node( _containerNode );
    if ( iDsc->maxSize ) addAttribute( _containerNode, "maxSize", *iDsc->maxSize );

    ActorSerializer actorSerializer(_document, _containerNode);
    for ( ActorDescriptionPtr content : iDsc->content )
    {
      actorSerializer.serialize(content);
    }
  }

  return iDsc != nullptr;
}

}

