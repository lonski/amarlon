#include "single_neighbour_selector.h"
#include <utils/direction_selector.h>
#include <world/map.h>
#include <Actor/Actor.h>
#include <engine.h>
#include <gui/gui.h>

namespace amarlon {

SingleNeighbourSelector::SingleNeighbourSelector()
{
}

std::vector<Actor*> SingleNeighbourSelector::select(Actor *executor, Map *map, bool (*filterFun)(Actor *))
{
  Engine::instance().gui().setStatusMessage("Select direction...");

  int dx(0), dy(0);

  DirectionSelector dSelector;
  dSelector.select(dx, dy);

  Engine::instance().gui().clearStatusMessage();
  Engine::instance().render();

  return map->getActors(executor->getX()+dx, executor->getY()+dy, filterFun);
}

Actor *SingleNeighbourSelector::selectFirst(Actor *executor, Map *map, bool (*filterFun)(Actor *))
{
  std::vector<Actor*> targets = select(executor, map, filterFun);
  return targets.empty() ? nullptr : targets.front();
}

}
