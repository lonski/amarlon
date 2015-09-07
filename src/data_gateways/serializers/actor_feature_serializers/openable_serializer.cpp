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

void OpenableSerializer::serializeOpenableCommonPart(xml_node<>* openableNode, OpenablePtr openable)
{
  if ( openableNode && openable && _document )
  {
    addAttribute( openableNode, "lockId", openable->getLockId() );
    addAttribute( openableNode, "locked", static_cast<int>(openable->isLocked()) );
  }
}

}
