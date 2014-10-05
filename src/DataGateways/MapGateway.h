#ifndef MAPGATEWAY_H
#define MAPGATEWAY_H

#include <map>
#include <World/MapId.h>

class Map;

class MapGateway
{
public:
  MapGateway();
  Map* fetch(MapId id);
  void loadMaps(std::string fn);
  void saveMaps(std::string fn);

private:
  std::map<MapId, Map*> _maps;

};

#endif // MAPGATEWAY_H
