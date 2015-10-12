#include "map_gateway.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>
#include <xml/rapidxml_print.hpp>
#include <map.h>
#include <actor_type.h>
#include <actor.h>
#include <actor_parser.h>
#include <map_serializer.h>

namespace amarlon {

using namespace rapidxml;
using namespace std;

MapGateway::MapGateway()
{
}

MapGateway::~MapGateway()
{
}

MapPtr MapGateway::fetch(MapId id)
{
  MapPtr map;

  auto mIter = _maps.find(id);
  if ( mIter != _maps.end() )
  {
    map = mIter->second->clone();
  }

  return map;
}

bool MapGateway::load(const string& fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buf;
    buf.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buf.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buf[0]);

    parseMaps(doc);

    return true;
  }
  return false;
}

void MapGateway::parseMaps(rapidxml::xml_document<>& doc)
{
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

bool MapGateway::store(const string& fn)
{
  ofstream ofs(fn);
  if ( ofs.is_open() )
  {
    ofs << *serializeMaps();
    return true;
  }
  return false;
}

}

