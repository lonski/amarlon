#include "single_neighbour_selector.h"
#include <direction_selector.h>
#include <map.h>
#include <actor.h>
#include <engine.h>
#include <gui.h>

namespace amarlon {

SingleNeighbourSelector::SingleNeighbourSelector(const std::string& selectionMessage)
  : TargetSelector(selectionMessage)
  , _selector( new DirectionSelector )
{
}

Target SingleNeighbourSelector::select(std::function<bool(ActorPtr)> filterFun)
{
  Engine::instance().getGui().setStatusMessage( _selectionMessage );
  TCODConsole::root->flush();
  MapPtr map = Engine::instance().getPlayer()->getMap();
  ActorPtr player = Engine::instance().getPlayer();

  int dx(0), dy(0);
  bool selected = _selector->select(dx, dy);

  Engine::instance().getGui().clearStatusMessage();
  Engine::instance().render();

  return selected ? Target(map->getActors(player->getX()+dx, player->getY()+dy, filterFun),
                           player->getX()+dx,
                           player->getY()+dy)
                  : Target();
}

}

