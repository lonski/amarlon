#include "map_parser.h"
#include <string>
#include <xml_utils.h>
#include <map.h>
#include <actor_parser.h>
#include <actor.h>
#include <teleport_action.h>
#include <base64.h>
#include <fstream>

namespace amarlon {

MapParser::MapParser()
  : _actorParser( new ActorParser)
{
}

MapParser::MapParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
  , _actorParser( new ActorParser )
{
}

MapPtr MapParser::parse()
{
  _map.reset();

  if ( _xml )
  {
    int x = getAttribute<int>(_xml, "width");
    int y = getAttribute<int>(_xml, "height");
    MapId id = static_cast<MapId>(getAttribute<int>(_xml, "id"));
    std::string tilesInStr = getNodeValue<std::string>( _xml->first_node("Tiles") );

    if ( !tilesInStr.empty())
    {
      _map.reset( new Map(x, y, id) );
      std::string decoded_tiles = base64_decode( tilesInStr );
      _map->deserializeTiles( std::vector<unsigned char>{decoded_tiles.begin(), decoded_tiles.end()} );

      parseActors();
    }

    parseActions();
  }
  _map->updateTiles();
  return _map;
}

void MapParser::parseActions()
{
  rapidxml::xml_node<>* onExitNode = _xml->first_node("OnExit");
  if ( onExitNode != nullptr )
  {
    rapidxml::xml_node<>* directionNode = onExitNode->first_node("Direction");
    while ( directionNode != nullptr )
    {
      Direction dir = static_cast<Direction>( getAttribute<int>(directionNode, "id") );
      rapidxml::xml_node<>* teleportNode = directionNode->first_node("Teleport");
      if ( teleportNode != nullptr )
      {
        MapId mapId = static_cast<MapId>( getAttribute<int>(teleportNode, "mapId") );
        int x = getAttribute<int>(teleportNode, "x");
        int y = getAttribute<int>(teleportNode, "y");
        _map->_exitActions[dir] = std::make_shared<TeleportAction>(mapId, x, y);
      }

      directionNode = directionNode->next_sibling();
    }
  }
}

void MapParser::parseActors()
{
  rapidxml::xml_node<>* actorsRoot = _xml->first_node("Actors");
  if (actorsRoot != nullptr)
  {
    rapidxml::xml_node<>* actorNode = actorsRoot->first_node("Actor");
    while ( actorNode != nullptr )
    {
      _actorParser->setSource( actorNode );
      _map->addActor( _actorParser->parse() );
      actorNode = actorNode->next_sibling();
    }
  }
}

}

