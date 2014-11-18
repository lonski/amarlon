#include "map_serializer.h"
#include <string>
#include <world/map.h>

using namespace rapidxml;
using namespace std;

namespace amarlon {

bool MapSerializer::serialize(MapPtr map)
{
  /*
   * TODO: at the momment theres is only tiles serialization
   * -> refactor the tile serializtion
   * -> implement actors serialization
   */
  bool serialized = false;

  if ( _xml != nullptr && _document != nullptr )
  {
    xml_node<>* mapNode = _document->allocate_node(node_element, "Map");
    _xml->append_node(mapNode);

    string widthS = to_string(map->getWidth());
    string heightS = to_string(map->getHeight());
    string idS = to_string( static_cast<int>(map->getId()) );

    xml_attribute<>* aWidth = _document->allocate_attribute("width", _document->allocate_string(widthS.c_str()) );
    xml_attribute<>* aHeight = _document->allocate_attribute("height", _document->allocate_string(heightS.c_str()) );
    xml_attribute<>* aId = _document->allocate_attribute("id", _document->allocate_string(idS.c_str()) );

    mapNode->append_attribute( aWidth );
    mapNode->append_attribute( aHeight );
    mapNode->append_attribute( aId );

    string strTiles = map->tilesToStr();

    xml_node<>* tiles = _document->allocate_node(node_element, "Tiles", _document->allocate_string(strTiles.c_str()) );
    mapNode->append_node(tiles);

    serialized = true;
  }

  return serialized;

}

}
