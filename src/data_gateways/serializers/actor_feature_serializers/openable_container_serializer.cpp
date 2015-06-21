#include "openable_container_serializer.h"
#include <openable_container.h>

using namespace rapidxml;

namespace amarlon {

OpenableContainerSerializer::OpenableContainerSerializer()
  : OpenableContainerSerializer(nullptr, nullptr)
{
}

OpenableContainerSerializer::OpenableContainerSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : OpenableSerializer(document, xmlNode)
{
}

OpenableContainerSerializer::~OpenableContainerSerializer()
{
}

bool OpenableContainerSerializer::serialize(ActorFeaturePtr af)
{
  OpenableContainerPtr cont = std::dynamic_pointer_cast<OpenableContainer>(af);
  if ( cont && _document && _xml )
  {
    xml_node<>* _contNode = _document->allocate_node(node_element, "OpenableContainer");
    _xml->append_node( _contNode );

    OpenableSerializer::serializeOpenableCommonPart(_contNode, cont);
  }
  return cont != nullptr;
}

}
