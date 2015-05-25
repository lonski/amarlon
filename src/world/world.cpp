#include "world.h"
#include <map.h>

namespace amarlon {

World::World()
{
}

MapPtr World::getCurrentMap()
{
  return getMap(_currentMap);
}

MapPtr World::getMap(MapId id)
{
  MapPtr map;

  auto mIter = _maps.find(id);
  if ( mIter != _maps.end() )
  {
    map = mIter->second;
  }
  else
  {
    map = Map::Gateway.fetch(id);
    _maps.insert( std::make_pair(id, map) );
  }

  return map;
}

void World::changeMap(MapId id)
{
  _currentMap = id;
}

}

