#ifndef MAPGATEWAY_H
#define MAPGATEWAY_H

#include <map>
#include <vector>
#include <memory>
#include "xml/rapidxml_print.hpp"
#include "world/map_id.h"
#include "data_gateways/parsers/map_parser.h"

namespace amarlon {

class Map;
class Actor;

typedef std::shared_ptr<Map> MapPtr;

class MapGateway
{
public:
  MapGateway();

  MapPtr fetch(MapId id);
  void loadMaps(std::string fn);
  void saveMaps(std::string fn);

private:
  MapParser _mapParser;
  std::map<MapId, MapPtr> _maps;  

  void parseMaps(std::vector<char> &buf);
  std::shared_ptr< rapidxml::xml_document<> > serializeMaps();
};

}

#endif // MAPGATEWAY_H
