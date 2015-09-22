#include "inventory_serializer.h"
#include <inventory.h>
#include <actor_serializer.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

InventorySerializer::InventorySerializer()
  : InventorySerializer(nullptr, nullptr)
{
}

InventorySerializer::InventorySerializer(xml_document<> *document, xml_node<> *xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

InventorySerializer::~InventorySerializer()
{
}

bool InventorySerializer::serialize(ActorFeaturePtr af)
{
  InventoryPtr container = std::dynamic_pointer_cast<Inventory>(af);
  if ( container && _document && _xml )
  {
    xml_node<>* _containerNode = _document->allocate_node(node_element, "Inventory");
    _xml->append_node( _containerNode );
    addAttribute( _containerNode, "maxSize", container->slotCount() );

    ActorSerializer actorSerializer(_document, _containerNode);
    for ( ActorPtr content : container->items() )
    {
      actorSerializer.serialize(content, "Content");
    }
  }

  return container != nullptr;
}

}

