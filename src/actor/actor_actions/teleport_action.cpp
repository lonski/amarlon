#include "teleport_action.h"
#include <actor.h>
#include <map.h>
#include <engine.h>

namespace amarlon {

TeleportAction::TeleportAction(MapId map, int x, int y)
  : _map(map)
  , _x(x)
  , _y(y)
{
}

TeleportAction::~TeleportAction()
{
}

bool TeleportAction::perform(ActorPtr performer)
{
  removeFromCurrentMap(performer);

  MapPtr newMap = Map::Gateway.fetch( _map );
  performer->setPosition(_x, _y);
  newMap->addActor( performer );

  if ( performer == Actor::Player )
  {
    Engine::instance().setCurrentMap( newMap );
    Engine::instance().render();
  }

  return true;
}

void TeleportAction::removeFromCurrentMap(ActorPtr performer)
{
  MapPtr currentMap = performer->getMap();
  if ( currentMap )
  {
    currentMap->removeActor(performer);
  }
}

}
