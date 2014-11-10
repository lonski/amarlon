#include "single_neighbour_selector.h"
#include <utils/direction_selector.h>
#include <world/map.h>
#include <Actor/Actor.h>

namespace amarlon {

SingleNeighbourSelector::SingleNeighbourSelector()
{
}

std::vector<Actor*> SingleNeighbourSelector::select(Actor *executor, Map *map, bool (*filterFun)(Actor *))
{
  int dx(0), dy(0);

  DirectionSelector dSelector;
  dSelector.select(dx, dy);

  return map->getActors(executor->getX()+dx, executor->getY()+dy, filterFun);
}

}
