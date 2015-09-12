#include "single_neighbour_selector.h"
#include "utils/direction_selector.h"
#include "world/map.h"
#include "actor/actor.h"
#include "engine.h"
#include "gui/gui.h"

namespace amarlon {

SingleNeighbourSelector::SingleNeighbourSelector(const std::string& selectionMessage)
  : TargetSelector(selectionMessage)
{
}

Target SingleNeighbourSelector::select(std::function<bool(ActorPtr)> filterFun)
{
  Engine::instance().getGui().setStatusMessage( _selectionMessage );
  TCODConsole::root->flush();
  MapPtr map = Engine::instance().getPlayer()->getMap();
  ActorPtr player = Engine::instance().getPlayer();

  int dx(0), dy(0);

  DirectionSelector dSelector;
  dSelector.select(dx, dy);

  Engine::instance().getGui().clearStatusMessage();
  Engine::instance().render();

  assert( map != nullptr );

  return Target(map->getActors(player->getX()+dx, player->getY()+dy, filterFun),
                player->getX()+dx,
                player->getY()+dy);
}

}
