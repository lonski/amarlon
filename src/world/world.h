#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <map>
#include <map_id.h>
#include <map_gateway.h>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

class World : public MapGateway
{
public:
  World();
  virtual ~World();

  virtual MapPtr fetch(MapId id);
  virtual MapPtr getCurrentMap();
  virtual void changeMap(MapId id);

private:  
  MapId _currentMap;

};

}

#endif // WORLD_H
