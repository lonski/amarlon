#include "openable_serializer.h"
#include <openable.h>
#include <utils.h>
#include <xml_utils.h>
#include <openable_description.h>

using namespace rapidxml;

namespace amarlon {

OpenableSerializer::OpenableSerializer()
  : OpenableSerializer(nullptr, nullptr)
{
}

OpenableSerializer::OpenableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
}

OpenableSerializer::~OpenableSerializer()
{
}

bool OpenableSerializer::serialize(DescriptionPtr dsc)
{
  OpenableDescriptionPtr oDsc = std::dynamic_pointer_cast<OpenableDescription>(dsc);
  if ( oDsc && _xml && _document )
  {
    if ( oDsc->any() )
    {
      xml_node<>* openableNode = _document->allocate_node(node_element, "Openable");
      _xml->append_node( openableNode );

      if ( oDsc->lockId ) addAttribute( openableNode, "lockId",   *oDsc->lockId );
      if ( oDsc->locked ) addAttribute( openableNode, "locked",   (int)*oDsc->locked );
      if ( oDsc->lockLevel ) addAttribute( openableNode, "lockLevel", *oDsc->lockLevel );
      if ( oDsc->scriptId ) addAttribute( openableNode, "scriptId", *oDsc->scriptId );
      if ( oDsc->closed ) addAttribute( openableNode, "closed",   (int)*oDsc->closed );
    }
    return true;
  }
  return false;
}


}

