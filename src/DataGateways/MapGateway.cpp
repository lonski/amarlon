#include "MapGateway.h"
#include "World/Map.h"
#include "Actor/ActorType.h"
#include "Actor/Actor.h"
#include <xml/rapidxml_print.hpp>
#include "Parsers/ActorParser.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>

namespace amarlon {

using namespace rapidxml;
using namespace std;

MapGateway::MapGateway()
{
}

Map* MapGateway::fetch(MapId id)
{
  Map* map = nullptr;

  if (_maps.count(id))
  {
    map = _maps[id];
  }

  return map;
}

void MapGateway::loadMaps(string fn)
{
  ifstream ifs(fn);
  vector<char> buf;
  buf.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
  buf.push_back('\0');

  xml_document<> doc;
  doc.parse<0>(&buf[0]);

  xml_node<>* maps = doc.first_node("Maps");

  xml_node<>* mapNode = maps->first_node("Map");
  while(mapNode != nullptr)
  {
    int x = stoi(mapNode->first_attribute("width")->value());
    int y = stoi(mapNode->first_attribute("height")->value());
    MapId id = (MapId)stoi(mapNode->first_attribute("id")->value());

    xml_node<>* tilesNode = mapNode->first_node("Tiles");
    string fillStr = tilesNode->value();
    Map* map = new Map(x, y, id);    
    map->fill( fillStr );

    xml_node<>* actorsRoot = mapNode->first_node("Actors");
    if (actorsRoot != nullptr)
    {
      xml_node<>* actorNode = actorsRoot->first_node("Actor");
      while ( actorNode != nullptr )
      {
        int aX = stoi(actorNode->first_attribute("x")->value());
        int aY = stoi(actorNode->first_attribute("y")->value());
        ActorType aId = (ActorType)stoi(actorNode->first_attribute("id")->value());

        Actor* actor = new Actor(aId, aX, aY);

        overwriteActorFeatures(actorNode, actor);

        map->addActor( actor );

        actorNode = actorNode->next_sibling();
      }
    }

    _maps[id] = map;

    mapNode = mapNode->next_sibling();
  }

}

void MapGateway::overwriteActorFeatures(xml_node<>* actorNode, Actor* actor)
{
  ActorParser actorParser(actorNode);

  unique_ptr<ContainerDescription> dscContainer( actorParser.parseContainerDsc() );
  unique_ptr<PickableDescription>  dscPickable ( actorParser.parsePickableDsc() );
  unique_ptr<OpenableDescription>  dscOpenable ( actorParser.parseOpenableDsc() );
  unique_ptr<FighterDescription>   dscFighter  ( actorParser.parseFighterDsc() );
  unique_ptr<AiDescription>        dscAi       ( actorParser.parseAiDsc() );

  if ( dscContainer ) actor->setAfContainer( Container::create(*dscContainer) );
  if ( dscPickable  ) actor->setAfPickable ( Pickable::create(*dscPickable) );
  if ( dscOpenable  ) actor->setAfOpenable ( Openable::create(*dscOpenable) );
  if ( dscFighter   ) actor->setAfFighter  ( Fighter::create(*dscFighter) );
  if ( dscAi        ) actor->setAfAi       ( Ai::create(*dscAi) );
}

void MapGateway::saveMaps(string fn)
{
  xml_document<> doc;

  xml_node<>* mapsNode = doc.allocate_node(node_element, "Maps");
  doc.append_node(mapsNode);

  //auto m = _maps.begin();
  for (auto m = _maps.begin(); m != _maps.end(); ++m)
  {
    MapId id = m->first;
    Map* map = m->second;

    xml_node<>* mapNode = doc.allocate_node(node_element, "Map");
    mapsNode->append_node(mapNode);


    string widthS = to_string(map->getWidth());
    string heightS = to_string(map->getHeight());
    string idS = to_string((int)id);

    xml_attribute<>* aWidth = doc.allocate_attribute("width", doc.allocate_string(widthS.c_str()) );
    xml_attribute<>* aHeight = doc.allocate_attribute("height", doc.allocate_string(heightS.c_str()) );
    xml_attribute<>* aId = doc.allocate_attribute("id", doc.allocate_string(idS.c_str()) );

    mapNode->append_attribute( aWidth );
    mapNode->append_attribute( aHeight );
    mapNode->append_attribute( aId );

    string strTiles = map->tilesToStr();

    xml_node<>* tiles = doc.allocate_node(node_element, "Tiles", doc.allocate_string(strTiles.c_str()) );
    mapNode->append_node(tiles);

  }

  //save
  ofstream ofs(fn);
  ofs << doc;

}

}
