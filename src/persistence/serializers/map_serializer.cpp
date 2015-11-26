#include "map_serializer.h"
#include <string>
#include <world/map.h>
#include <utils.h>
#include <xml_utils.h>
#include <actor.h>
#include <iostream>
#include <libtcod.hpp>
#include <actor_action.h>
#include <base64.h>

using namespace rapidxml;
using namespace std;

namespace amarlon {

MapSerializer::MapSerializer()
  : _mapNode(nullptr)
{
}

MapSerializer::MapSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
  , _mapNode(nullptr)
{
}

MapSerializer::~MapSerializer()
{
}

bool MapSerializer::serialize(MapPtr map)
{
  bool serialized = false;
  _map = map;

  if ( _xml && _document && _map )
  {
    _mapNode = _document->allocate_node(node_element, "Map");
    _xml->append_node(_mapNode);

    serializeAttributes();
    serializeExitActions();
    serializeActors();

    serialized = true;
  }

  return serialized;
}

void MapSerializer::serializeAttributes()
{
  addAttribute(_mapNode, "height", _map->getHeight());
  addAttribute(_mapNode,  "width", _map->getWidth());
  addAttributeEnum(_mapNode, "id", _map->getId());
  _mapNode->append_node( createNode(_document, "Tiles", _map->serializeTiles()) );

}

void MapSerializer::serializeExitActions()
{
  xml_node<>* exitActionsNode = createNode(_document, "OnExit", "");
  _mapNode->append_node( exitActionsNode );

  for ( const auto& pair : _map->getExitActions() )
  {
    xml_node<>* directionNode = createNode(_document, "Direction", "");
    exitActionsNode->append_node(directionNode);
    addAttributeEnum( directionNode, "id", pair.first );

    _actionSerializer.setDestination(_document, directionNode);
    _actionSerializer.serialize( pair.second->toDescriptionStruct() );
  }
}

void MapSerializer::serializeActors()
{
  xml_node<>* actorsNode = createNode(_document, "Actors", "");
  _mapNode->append_node( actorsNode );

  _actorSerializer.setDestination(_document, actorsNode);
  for ( ActorPtr actor : _map->getActors() )
  {
    _actorSerializer.serialize(actor);
  }
}

}

