#include "teleport_action.h"
#include <actor.h>
#include <map.h>
#include <world.h>
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

ActorActionResult TeleportAction::perform(ActorPtr performer)
{  
  removeFromCurrentMap(performer);
  performer->setPosition(_x, _y);

  MapPtr newMap = Engine::instance().getWorld().fetch( _map );
  newMap->addActor( performer );

  if ( performer == Engine::instance().getPlayer() )
  {
    Engine::instance().getWorld().changeMap( _map );
    Engine::instance().render();
    TCODConsole::root->flush();
  }

  return ActorActionResult::Ok;
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

DescriptionPtr TeleportAction::toDescriptionStruct()
{
  ActorActionDescriptionPtr aDsc( new ActorActionDescription );
  aDsc->teleport_MapId = static_cast<int>(_map);
  aDsc->teleport_x = _x;
  aDsc->teleport_y = _y;
  return aDsc;
}

void TeleportAction::removeFromCurrentMap(ActorPtr performer)
{
  MapPtr currentMap = performer->getMap();
  if ( currentMap )
  {
    currentMap->removeActor(performer);
    performer->setMap(nullptr);
  }
}

}

