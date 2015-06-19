#include "action_serializer.h"
#include <teleport_action.h>
#include <utils.h>
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

bool ActionSerializer::serialize(ActorActionPtr action)
{
  bool serialized = false;

  if ( _document && _xml )
  {
    TeleportActionPtr tAction = std::dynamic_pointer_cast<TeleportAction>(action);
    if ( tAction )
    {
      xml_node<>* actionNode = _document->allocate_node(node_element, "Teleport");
      _xml->append_node( actionNode );

      actionNode->append_attribute( _document->allocate_attribute( "mapId", _document->allocate_string( toStr(static_cast<int>( tAction->getMapId() )).c_str() )));
      actionNode->append_attribute( _document->allocate_attribute( "x", _document->allocate_string( toStr( tAction->getX() ).c_str() )));
      actionNode->append_attribute( _document->allocate_attribute( "y", _document->allocate_string( toStr( tAction->getY() ).c_str() )));

      serialized = true;
    }
    else
    {
      // at the momment support only for teleport actions.
      // if try to seriazlize not supported action then throw
      // and remind to implement it first
      throw amarlon_exeption("This action serializing is not implemented!");
    }
  }

  return serialized;
}

}
