#include "engine.h"
#include "World/map.h"
#include "Actor/actor.h"

int Engine::FovRadius = 20;

Engine::Engine()
  : _console(TCODConsole::root)
{
}

void Engine::init()
{
  //temp init
  Map::Tiles.loadTiles("d:/tiles.xml");
  Actor::DB.loadActors("d:/actors.xml");
  Map::Gateway.loadMaps("d:/maps.xml");

  setCurrentMap( Map::Gateway.fetch(MapId::GameStart) );

  _player = new Actor(ActorType::Player, 40, 40);
}

void Engine::render()
{
  _console->clear();
  if (_currentMap != nullptr)
  {
    _currentMap->computeFov(_player->getX(), _player->getY(), FovRadius);
    _currentMap->render(_console);
  }

  _console->putChar(_player->getX(), _player->getY(), _player->getChar());
  _console->setCharForeground(_player->getX(), _player->getY(), _player->getColor());
}

void Engine::processKey(TCOD_key_t &key)
{
  CommandExecutor::execute(key, _currentMap, _player);
}

Map *Engine::currentMap() const
{
  return _currentMap;
}

void Engine::setCurrentMap(Map *currentMap)
{
  _currentMap = currentMap;
}

