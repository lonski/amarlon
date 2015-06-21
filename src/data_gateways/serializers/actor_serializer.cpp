#include "actor_serializer.h"
#include <utils.h>
#include <actor.h>
#include <pickable_serializer.h>
#include <destroyable_serializer.h>
#include <container_serializer.h>

using namespace rapidxml;

namespace amarlon {

ActorSerializer::ActorSerializer()
  : ActorSerializer(nullptr, nullptr)
{
}

ActorSerializer::ActorSerializer(xml_document<>* document, xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
  _afSerializers.push_back( std::make_shared<PickableSerializer>() );
  _afSerializers.push_back( std::make_shared<DestroyableSerializer>() );
  _afSerializers.push_back( std::make_shared<ContainerSerializer>() );
}

ActorSerializer::~ActorSerializer()
{
}

bool ActorSerializer::serialize(ActorPtr actor, const char* nodeName)
{
  bool serialized = false;

  if ( _document && _xml )
  {
    _actorNode = _document->allocate_node(node_element, nodeName);
    _xml->append_node( _actorNode );

    _actorNode->append_attribute( _document->allocate_attribute( "id",_document->allocate_string( toStr( static_cast<int>(actor->getId()) ).c_str()) ) );
    _actorNode->append_attribute( _document->allocate_attribute( "x",_document->allocate_string( toStr( actor->getX() ).c_str()) ) );
    _actorNode->append_attribute( _document->allocate_attribute( "y",_document->allocate_string( toStr( actor->getY() ).c_str()) ) );

    for ( const auto& afPair : actor->getFeatures() )
    {
      for ( auto serializer : _afSerializers )
      {
        serializer->setDestination(_document, _actorNode);
        if ( serializer->serialize(afPair.second) ) break;
      }
    }
  }

  return serialized;
}

}
