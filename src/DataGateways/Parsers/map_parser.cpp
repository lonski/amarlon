#include "map_parser.h"
#include <string>
#include <world/map.h>
#include <utils/xml_utils.h>
#include <Parsers/ActorParser.h>
#include <Actor/Actor.h>

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
      _map->fill( tilesInStr );

      parseActors();
    }
  }

  return _map;
}

void MapParser::parseActors()
{
  rapidxml::xml_node<>* actorsRoot = _xml->first_node("Actors");
  if (actorsRoot != nullptr)
  {
    rapidxml::xml_node<>* actorNode = actorsRoot->first_node("Actor");
    while ( actorNode != nullptr )
    {
      _map->addActor( parseActor(actorNode) );
      actorNode = actorNode->next_sibling();
    }
  }
}

Actor* MapParser::parseActor(rapidxml::xml_node<>* actorNode)
{
  _actorParser->setSource( actorNode );

  int aX = getAttribute<int>(actorNode, "x");
  int aY = getAttribute<int>(actorNode, "y");
  ActorType aId = static_cast<ActorType>(getAttribute<int>(actorNode, "id"));

  Actor* actor = new Actor(aId, aX, aY, _map.get());
  overWriteActorFeatures(actor);

  return actor;
}

void MapParser::overWriteActorFeatures(Actor* actor)
{
  for (int f = ActorFeature::FT_NULL+1; f != ActorFeature::FT_END; ++f)
  {
    ActorFeature::Type featureType = static_cast<ActorFeature::Type>( f );

    std::unique_ptr<Description> dsc( _actorParser->parseFeatureDsc(featureType) );
    if ( dsc ) actor->insertFeature( ActorFeature::create(featureType, dsc.get()) );
  }
}

}
