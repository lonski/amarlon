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
  performer->setPosition(_x, _y);

  MapPtr newMap = Engine::instance().getWorld().getMap( _map );
  newMap->addActor( performer );

  if ( performer == Actor::Player )
  {
    Engine::instance().getWorld().changeMap( _map );
    Engine::instance().render();
  }

  return true;
}

ActorActionUPtr TeleportAction::clone()
{
  TeleportActionUPtr cloned = std::make_unique<TeleportAction>(_map, _x, _y);
  return std::move(cloned);
}

MapId TeleportAction::getMapId() const
{
  return _map;
}

int TeleportAction::getX() const
{
  return _x;
}

int TeleportAction::getY() const
{
  return _y;
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
