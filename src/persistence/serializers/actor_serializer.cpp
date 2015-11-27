#include "actor_serializer.h"
#include <utils.h>
#include <xml_utils.h>
#include <actor.h>
#include <pickable_serializer.h>
#include <wearer_serializer.h>
#include <openable_serializer.h>
#include <status_effects_manager.h>
#include <status_effect.h>
#include <trap_serializer.h>

#include <ai_serializer.h>
#include <character_serializer.h>
#include <destroyable_serializer.h>
#include <inventory_serializer.h>

using namespace rapidxml;

namespace amarlon {

ActorSerializer::ActorSerializer()
  : ActorSerializer(nullptr, nullptr)
{
}

ActorSerializer::ActorSerializer(xml_document<>* document, xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
  , _actorNode(nullptr)
{
  _afSerializers.push_back( std::make_shared<PickableSerializer>() );
  _afSerializers.push_back( std::make_shared<WearerSerializer>() );
  _afSerializers.push_back( std::make_shared<OpenableSerializer>() );
  _afSerializers.push_back( std::make_shared<TrapSerializer>() );

  _featureSerializers.push_back( std::make_shared<InventorySerializer>() );
  _featureSerializers.push_back( std::make_shared<DestroyableSerializer>() );
  _featureSerializers.push_back( std::make_shared<CharacterSerializer>() );
  _featureSerializers.push_back( std::make_shared<AiSerializer>() );
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

    addAttributeEnum( _actorNode, "id", actor->getType() );
    addAttribute( _actorNode, "x", actor->getX() );
    addAttribute( _actorNode, "y", actor->getY() );
    addAttribute( _actorNode, "fovOnly", actor->isFovOnly() );
    addAttribute( _actorNode, "transparent", actor->isTransparent() );
    addAttribute( _actorNode, "blocks", actor->isBlocking() );
    if (!actor->isVisible()) addAttribute( _actorNode, "visible", actor->isVisible() );
    addAttribute( _actorNode, "tilePriority", actor->getTileRenderPriority() );
    addAttribute( _actorNode, "name", actor->getName().c_str() );
    addAttribute( _actorNode, "color", colorToStr( actor->getColor() ) );
    addAttribute( _actorNode, "character", actor->getSymbol() );

    //Serialize Status Effects
    auto effects = actor->getStatusEffects().getEffects();
    if ( !effects.empty() )
    {
      xml_node<>* semNode = _document->allocate_node(node_element, "StatusEffects");
      _actorNode->append_node(semNode);
      for(auto e : effects)
      {
        xml_node<>* eNode = _document->allocate_node(node_element, "StatusEffect");
        semNode->append_node( eNode );
        addAttribute(eNode, "name", e->getName());
        addAttribute(eNode, "script", e->getScript());
        addAttribute(eNode, "duration", e->getDuration());
      }
    }

    //Serialize ActorFeatures
    for ( const auto& afPair : actor->_features )
    {
      for ( auto serializer : _afSerializers )
      {
        serializer->setDestination(_document, _actorNode);
        if ( serializer->serialize(afPair.second) ) break;
      }
      for ( auto serializer : _featureSerializers )
      {
        serializer->setDestination(_document, _actorNode);
        if ( serializer->serialize(afPair.second->toDescriptionStruct()) ) break;
      }
    }
  }

  return serialized;
}

bool ActorSerializer::serialize(DescriptionPtr dsc)
{
  //TODO
  return true;
}

}

