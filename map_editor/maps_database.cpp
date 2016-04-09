#include "maps_database.h"
#include <fstream>
#include <vector>
#include <xml/rapidxml.hpp>
#include <persistence/parsers/map_parser.h>
#include <persistence/serializers/map_serializer.h>
#include <xml/rapidxml_print.hpp>

using namespace rapidxml;

namespace amarlon { namespace map_editor {

MapsDatabase::MapsDatabase()
{

}

bool MapsDatabase::load(const std::string &fn)
{
  std::ifstream ifs(fn);
  _maps.clear();

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buf[0]);

    xml_node<>* maps = doc.first_node("Maps");
    xml_node<>* mapNode = maps ? maps->first_node("Map") : nullptr;

    MapParser parser;
    while(mapNode != nullptr)
    {
      parser.setSource( mapNode );

      MapDescriptionPtr dsc = parser.parseDescription();

      if ( dsc ) _maps[ (MapId)dsc->id ] = dsc;

      mapNode = mapNode->next_sibling();
    }

    return true;
  }
  return false;
}

bool MapsDatabase::store(const std::string &fn)
{
  std::ofstream ofs(fn);
  if ( ofs.is_open() )
  {
    std::shared_ptr<xml_document<> > doc(new xml_document<>);

    xml_node<>* mapsNode = doc->allocate_node(node_element, "Maps");
    doc->append_node(mapsNode);

    MapSerializer _mapSerializer(doc.get(), mapsNode);
    for (auto m : _maps)
    {
      if (m.second) _mapSerializer.serialize( m.second );
    }

    ofs << *doc;
    return true;
  }
  return false;
}

size_t MapsDatabase::getMapCount() const
{
  return _maps.size();
}

std::map<MapId, MapDescriptionPtr> MapsDatabase::getMaps() const
{
  return _maps;
}

MapDescriptionPtr MapsDatabase::getMap(MapId id) const
{
  auto it = _maps.find(id);
  return it != _maps.end() ? it->second : nullptr;
}

}}
