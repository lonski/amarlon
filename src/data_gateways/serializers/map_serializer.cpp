#include "map_serializer.h"
#include <string>
#include <world/map.h>
#include <utils.h>
#include <xml_utils.h>

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
  /* TODO
   * -> implement actors serialization   
   */
  bool serialized = false;

  if ( _xml != nullptr && _document != nullptr )
  {    
    _map = map;
    _mapNode = _document->allocate_node(node_element, "Map");
    _xml->append_node(_mapNode);

    _mapNode->append_attribute( _document->allocate_attribute(    "height",_document->allocate_string( toStr(map->getHeight()).c_str()) ) );
    _mapNode->append_attribute( _document->allocate_attribute(    "width",_document->allocate_string( toStr(map->getWidth()).c_str()) ) );
    _mapNode->append_attribute( _document->allocate_attribute(    "id", _document->allocate_string( toStr(static_cast<int>(map->getId())).c_str()) ) );
    _mapNode->append_node( _document->allocate_node(node_element, "Tiles", _document->allocate_string( map->tilesToStr().c_str()) ) );

    serializeExitActions();

    _actorSerializer.setDestination(_document, _mapNode);
    for ( ActorPtr actor : _map->getActors() )
    {
      _actorSerializer.serialize(actor);
    }

    serialized = true;
  }

  return serialized;
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

}
