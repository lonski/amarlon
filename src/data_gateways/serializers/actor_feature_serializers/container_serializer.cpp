#include "container_serializer.h"
#include <container.h>
#include <actor_serializer.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

ContainerSerializer::ContainerSerializer()
  : ContainerSerializer(nullptr, nullptr)
{
}

ContainerSerializer::ContainerSerializer(xml_document<> *document, xml_node<> *xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

ContainerSerializer::~ContainerSerializer()
{
}

bool ContainerSerializer::serialize(ActorFeaturePtr af)
{
  ContainerPtr container = std::dynamic_pointer_cast<Container>(af);
  if ( container && _document && _xml )
  {
    xml_node<>* _containerNode = _document->allocate_node(node_element, "Container");
    _xml->append_node( _containerNode );
    addAttribute( _containerNode, "maxSize", container->slotCount() );

    ActorSerializer actorSerializer(_document, _containerNode);
    for ( ActorPtr content : container->content() )
    {
      actorSerializer.serialize(content, "Content");
    }
  }

  return container != nullptr;
}

}
