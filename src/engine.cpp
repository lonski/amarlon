#include "engine.h"
#include "World/map.h"
#include "Actor/actor.h"
#include <algorithm>

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

  Actor::Player = new Actor(ActorType::Player, 42, 28);
}

void Engine::render()
{
  _console->clear();
  if (_currentMap != nullptr)
  {
    _currentMap->computeFov(Actor::Player->getX(), Actor::Player->getY(), FovRadius);
    _currentMap->render(_console);
  }

  _console->putChar(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getChar());
  _console->setCharForeground(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getColor());
}

void Engine::updateAis()
{
  if (_currentMap != nullptr)
  {
    std::for_each(_currentMap->actors().begin(), _currentMap->actors().end(), [&](Actor* a)
    {
      if (a->afAi()) a->afAi()->update(_currentMap);
    });
  }
}

void Engine::processKey(TCOD_key_t &key)
{
  CommandExecutor::execute(key, _currentMap, Actor::Player);
}

Map *Engine::currentMap() const
{
  return _currentMap;
}

void Engine::setCurrentMap(Map *currentMap)
{
  _currentMap = currentMap;
}

