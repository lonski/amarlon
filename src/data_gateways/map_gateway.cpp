#include "map_gateway.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>
#include <xml/rapidxml_print.hpp>
#include "world/map.h"
#include "actor/actor_type.h"
#include "actor/actor.h"
#include "parsers/actor_parser.h"
#include "serializers/map_serializer.h"

namespace amarlon {

using namespace rapidxml;
using namespace std;

MapGateway::MapGateway()
{
}

MapPtr MapGateway::fetch(MapId id)
{
  MapPtr map(nullptr);

  if (_maps.count(id))
  {
    map = _maps[id];
  }

  return map;
}

void MapGateway::loadMaps(string fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buf;
    buf.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buf.push_back('\0');

    parseMaps(buf);
  }
}

void MapGateway::parseMaps(vector<char>& buf)
{
  xml_document<> doc;
  doc.parse<0>(&buf[0]);

  xml_node<>* maps = doc.first_node("Maps");
  xml_node<>* mapNode = maps ? maps->first_node("Map") : nullptr;

  while(mapNode != nullptr)
  {
    _mapParser.setSource( mapNode );
    MapPtr map = _mapParser.parse();
    if ( map ) _maps[ map->getId() ] = map;

    mapNode = mapNode->next_sibling();
  }
}

std::shared_ptr<xml_document<> > MapGateway::serializeMaps()
{
  std::shared_ptr<xml_document<> > doc(new xml_document<>);

  xml_node<>* mapsNode = doc->allocate_node(node_element, "Maps");
  doc->append_node(mapsNode);

  MapSerializer _mapSerializer(doc.get(), mapsNode);
  for (auto m : _maps) _mapSerializer.serialize( m.second );

  return doc;
}

void MapGateway::saveMaps(string fn)
{
  ofstream ofs(fn);
  if ( ofs.is_open() ) ofs << *serializeMaps();
}

}
