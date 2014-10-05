#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>

class Map;

class Engine
{
public:
  Engine();

  void render();

  Map *currentMap() const;
  void setCurrentMap(Map *currentMap);

private:
  Map* _currentMap;
  TCODConsole* _console;

};

#endif // ENGINE_H
