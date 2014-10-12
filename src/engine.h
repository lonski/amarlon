#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include "CommandExecutor.h"

class Map;
class Actor;

class Engine
{
public:
  static int FovRadius;

  Engine();

  void init();
  void render(); 
  void updateAis();
  void processKey(TCOD_key_t& key);

  Map *currentMap() const;
  void setCurrentMap(Map *currentMap);

private:
  TCODConsole* _console;
  Map* _currentMap;

};

#endif // ENGINE_H
