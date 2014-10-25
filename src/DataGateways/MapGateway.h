#ifndef MAPGATEWAY_H
#define MAPGATEWAY_H

#include <map>
#include <World/MapId.h>
#include <xml/rapidxml_print.hpp>

namespace amarlon {

class Map;
class Actor;

class MapGateway
{
public:
  MapGateway();
  Map* fetch(MapId id);
  void loadMaps(std::string fn);
  void saveMaps(std::string fn);

private:
  std::map<MapId, Map*> _maps;
  void overwriteActorFeatures(rapidxml::xml_node<>* actorNode, Actor* actor);

};

}

#endif // MAPGATEWAY_H
