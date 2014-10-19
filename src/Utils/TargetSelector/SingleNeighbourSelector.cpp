#include "SingleNeighbourSelector.h"
#include "Utils/DirectionSelector.h"
#include "World/Map.h"
#include "Actor/Actor.h"

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
