#include "engine.h"
#include "World/map.h"

Engine::Engine()
  : _console(TCODConsole::root)
{
}

void Engine::render()
{
  if (_currentMap != nullptr)
  {
    _currentMap->render(_console);
  }
}

Map *Engine::currentMap() const
{
  return _currentMap;
}

void Engine::setCurrentMap(Map *currentMap)
{
  _currentMap = currentMap;
}

