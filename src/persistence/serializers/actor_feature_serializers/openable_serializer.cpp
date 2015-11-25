#include "openable_serializer.h"
#include <openable.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

OpenableSerializer::OpenableSerializer()
  : OpenableSerializer(nullptr, nullptr)
{
}

OpenableSerializer::OpenableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

OpenableSerializer::~OpenableSerializer()
{
}

bool OpenableSerializer::serialize(ActorFeaturePtr af)
{
  OpenablePtr openable = std::dynamic_pointer_cast<Openable>(af);
  if ( openable && _xml && _document )
  {
    xml_node<>* openableNode = _document->allocate_node(node_element, "Openable");
    _xml->append_node( openableNode );

    addAttribute( openableNode, "lockId",   openable->getLockId() );
    addAttribute( openableNode, "locked",   static_cast<int>(openable->isLocked()) );
    addAttribute( openableNode, "lockLevel", static_cast<int>(openable->getLockLevel()) );
    addAttribute( openableNode, "scriptId", static_cast<int>(openable->getScriptId()) );
    addAttribute( openableNode, "closed",   static_cast<int>(openable->isClosed()) );
    return true;
  }
  return false;
}

}

