#include "world.h"
#include <map.h>

namespace amarlon {

World::World(MapGatewayPtr mapGateway)
  : _mapGateway(mapGateway)
{
}

World::~World()
{
}

MapPtr World::getCurrentMap()
{
  return fetch(_currentMap);
}

MapPtr World::fetch(MapId id)
{
  MapPtr map;

  auto mIter = _maps.find(id);
  if ( mIter != _maps.end() )
  {
    map = mIter->second;
  }
  else
  {
    map = _mapGateway->fetch(id);
    _maps.insert( std::make_pair(id, map) );
  }

  return map;
}

void World::changeMap(MapId id)
{
  _currentMap = id;
}

}

