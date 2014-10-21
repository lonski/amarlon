#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include "CommandExecutor.h"

class Map;
class Actor;
class Gui;

class Engine
{
public:
  static int FovRadius;

  Engine();
  ~Engine();

  void init();
  void update();
  void processKey(TCOD_key_t& key);

  Map* currentMap() const;
  void setCurrentMap(Map *currentMap);

  TCODConsole *getConsole() const;
  void setConsole(TCODConsole *getConsole);

  Gui *getGui() const;
  void setGui(Gui *getGui);

private:
  TCODConsole* _console;
  Map* _currentMap;
  Gui* _gui;

  void render();
  void updateAis();

};

#endif // ENGINE_H
