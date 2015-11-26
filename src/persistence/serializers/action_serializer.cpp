#include "action_serializer.h"
#include <actor_action_description.h>
#include <utils.h>
#include <xml_utils.h>
#include <amarlon_except.h>

using namespace rapidxml;

namespace amarlon {

ActionSerializer::ActionSerializer()
{
}

ActionSerializer::ActionSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* parentNode)
  : Serializer(document, parentNode)
{
}

ActionSerializer::~ActionSerializer()
{
}

bool ActionSerializer::serialize(DescriptionPtr dsc)
{
  bool serialized = false;

  if ( _document && _xml )
  {
    ActorActionDescriptionPtr tAction = std::dynamic_pointer_cast<ActorActionDescription>(dsc);
    if ( tAction )
    {
      xml_node<>* actionNode = _document->allocate_node(node_element, "Teleport");
      _xml->append_node( actionNode );

      addAttributeEnum( actionNode, "mapId", tAction->teleport_MapId );
      addAttribute( actionNode, "x", tAction->teleport_x );
      addAttribute( actionNode, "y", tAction->teleport_y );

      serialized = true;
    }
  }

  return serialized;

}

}

