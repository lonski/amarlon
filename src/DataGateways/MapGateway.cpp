#include "MapGateway.h"
#include "World/map.h"
#include "Actor/ActorType.h"
#include "Actor/actor.h"
#include <xml/rapidxml_print.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>

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

        map->addActor( new Actor(aId, aX, aY) );

        actorNode = actorNode->next_sibling();
      }
    }

    _maps[id] = map;

    mapNode = mapNode->next_sibling();
  }

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
