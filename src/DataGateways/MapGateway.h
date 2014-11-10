#ifndef MAPGATEWAY_H
#define MAPGATEWAY_H

#include <map>
#include <memory>
#include <world/map_id.h>
#include <xml/rapidxml_print.hpp>

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
  std::map<MapId, MapPtr> _maps;
  void overwriteActorFeatures(rapidxml::xml_node<>* actorNode, Actor* actor);

};

}

#endif // MAPGATEWAY_H
