#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <map>
#include <map_id.h>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

class World
{
public:
  World();

  MapPtr getCurrentMap();
  MapPtr getMap(MapId id);
  void changeMap(MapId id);

  /* TODO:
   * saving to file
   * loading from file
   */

private:
  std::map<MapId, MapPtr> _maps;
  MapId _currentMap;

};

}

#endif // WORLD_H
