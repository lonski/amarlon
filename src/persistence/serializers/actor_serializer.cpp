#include "actor_serializer.h"
#include <utils.h>
#include <xml_utils.h>
#include <actor_descriptions.h>
#include <ai_serializer.h>
#include <character_serializer.h>
#include <destroyable_serializer.h>
#include <inventory_serializer.h>
#include <openable_serializer.h>
#include <pickable_serializer.h>
#include <talker_serializer.h>
#include <trap_serializer.h>
#include <wearer_serializer.h>

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
  _featureSerializers.push_back( std::make_shared<WearerSerializer>() );
  _featureSerializers.push_back( std::make_shared<TrapSerializer>() );
  _featureSerializers.push_back( std::make_shared<TalkerSerializer>() );
  _featureSerializers.push_back( std::make_shared<PickableSerializer>() );
  _featureSerializers.push_back( std::make_shared<OpenableSerializer>() );
  _featureSerializers.push_back( std::make_shared<InventorySerializer>() );
  _featureSerializers.push_back( std::make_shared<DestroyableSerializer>() );
  _featureSerializers.push_back( std::make_shared<CharacterSerializer>() );
  _featureSerializers.push_back( std::make_shared<AiSerializer>() );
}

ActorSerializer::~ActorSerializer()
{
}

bool ActorSerializer::serialize(DescriptionPtr dsc)
{
  bool serialized = false;

  ActorDescriptionPtr aDsc = std::dynamic_pointer_cast<ActorDescription>(dsc);
  if ( dsc && _document && _xml )
  {
    _actorNode = _document->allocate_node(node_element, "Actor");
    _xml->append_node( _actorNode );

    if ( aDsc->id )           addAttribute( _actorNode, "id", *aDsc->id );
    if ( aDsc->x )            addAttribute( _actorNode, "x", *aDsc->x );
    if ( aDsc->y )            addAttribute( _actorNode, "y", *aDsc->y );
    if ( aDsc->fovOnly )      addAttribute( _actorNode, "fovOnly", (int)*aDsc->fovOnly );
    if ( aDsc->transparent )  addAttribute( _actorNode, "transparent", (int)*aDsc->transparent );
    if ( aDsc->blocks )       addAttribute( _actorNode, "blocks", (int)*aDsc->blocks );
    if ( aDsc->visible )      addAttribute( _actorNode, "visible", (int)*aDsc->visible );
    if ( aDsc->tilePriority ) addAttribute( _actorNode, "tilePriority", *aDsc->tilePriority );
    if ( aDsc->name )         addAttribute( _actorNode, "name", *aDsc->name );
    if ( aDsc->color )        addAttribute( _actorNode, "color", *aDsc->color );
    if ( aDsc->symbol )       addAttribute( _actorNode, "character", *aDsc->symbol );

    //Serialize Status Effects
    if ( !aDsc->statusEffects.empty() )
    {
      xml_node<>* semNode = _document->allocate_node(node_element, "StatusEffects");
      _actorNode->append_node(semNode);
      for(StatusEffectDsc e : aDsc->statusEffects)
      {
        xml_node<>* eNode = _document->allocate_node(node_element, "StatusEffect");
        semNode->append_node( eNode );
        addAttribute(eNode, "name", e.name);
        addAttribute(eNode, "script", e.script);
        addAttribute(eNode, "duration", e.duration);
      }
    }

    //Serialize ActorFeatures
    for ( const auto& afPair : aDsc->features )
    {
      for ( auto serializer : _featureSerializers )
      {
        serializer->setDestination(_document, _actorNode);
        if ( serializer->serialize(afPair.second) ) break;
      }
    }
  }

  return serialized;
}

}

