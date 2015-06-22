#include "map_serializer.h"
#include <string>
#include <world/map.h>
#include <utils.h>
#include <xml_utils.h>
#include <actor.h>
#include <iostream>

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
  _mapNode->append_attribute( _document->allocate_attribute(    "height",_document->allocate_string( toStr(_map->getHeight()).c_str()) ) );
  _mapNode->append_attribute( _document->allocate_attribute(    "width",_document->allocate_string( toStr(_map->getWidth()).c_str()) ) );
  _mapNode->append_attribute( _document->allocate_attribute(    "id", _document->allocate_string( toStr(static_cast<int>(_map->getId())).c_str()) ) );
  _mapNode->append_node( _document->allocate_node(node_element, "Tiles", _document->allocate_string( _map->tilesToStr().c_str()) ) );
}

void MapSerializer::serializeExitActions()
{
  xml_node<>* exitActionsNode = _document->allocate_node(node_element, "OnExit");
  _mapNode->append_node( exitActionsNode );

  for ( const auto& pair : _map->getExitActions() )
  {
    xml_node<>* directionNode = _document->allocate_node(node_element, "Direction");
    exitActionsNode->append_node(directionNode);
    directionNode->append_attribute( _document->allocate_attribute( "id", _document->allocate_string( toStr(static_cast<int>(pair.first)).c_str() )));

    _actionSerializer.setDestination(_document, directionNode);
    _actionSerializer.serialize(pair.second);
  }
}

void MapSerializer::serializeActors()
{
  xml_node<>* actorsNode = _document->allocate_node(node_element, "Actors");
  _mapNode->append_node( actorsNode );

  _actorSerializer.setDestination(_document, actorsNode);
  for ( ActorPtr actor : _map->getActors() )
  {
    _actorSerializer.serialize(actor);
  }
}

}
