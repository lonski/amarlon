#include "actor_serializer.h"
#include <utils.h>
#include <actor.h>

using namespace rapidxml;

namespace amarlon {

ActorSerializer::ActorSerializer()
{
}

ActorSerializer::ActorSerializer(xml_document<>* document, xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
}

ActorSerializer::~ActorSerializer()
{
}

bool ActorSerializer::serialize(ActorPtr actor)
{
  bool serialized = false;

  if ( _document && _xml )
  {
    _actorNode = _document->allocate_node(node_element, "Actor");
    _xml->append_node( _actorNode );

    _actorNode->append_attribute( _document->allocate_attribute( "id",_document->allocate_string( toStr( static_cast<int>(actor->getId()) ).c_str()) ) );
    _actorNode->append_attribute( _document->allocate_attribute( "x",_document->allocate_string( toStr( actor->getX() ).c_str()) ) );
    _actorNode->append_attribute( _document->allocate_attribute( "y",_document->allocate_string( toStr( actor->getY() ).c_str()) ) );

    //TODO: serialize the actor features
  }

  return serialized;
}

}
