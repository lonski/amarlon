#include "openable_door_serializer.h"
#include <openable_door.h>

using namespace rapidxml;

namespace amarlon {

OpenableDoorSerializer::OpenableDoorSerializer()
  : OpenableDoorSerializer(nullptr, nullptr)
{
}

OpenableDoorSerializer::OpenableDoorSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : OpenableSerializer(document, xmlNode)
{
}

OpenableDoorSerializer::~OpenableDoorSerializer()
{
}

bool OpenableDoorSerializer::serialize(ActorFeaturePtr af)
{
  OpenableDoorPtr door = std::dynamic_pointer_cast<OpenableDoor>(af);
  if ( door && _document && _xml )
  {
    xml_node<>* _doorNode = _document->allocate_node(node_element, "OpenableDoor");
    _xml->append_node( _doorNode );

    OpenableSerializer::serializeOpenableCommonPart(_doorNode, door);
  }
  return door != nullptr;
}

}
