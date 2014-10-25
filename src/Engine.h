#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include "CommandExecutor.h"

namespace amarlon {

class Map;
class Actor;

namespace gui {
  class Gui;
}
struct LogEntry;

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

  gui::Gui *getGui() const;
  void setGui(gui::Gui *getGui);

private:
  TCODConsole* _console;
  Map* _currentMap;
  gui::Gui* _gui;

  void render();
  void updateAis();
  std::vector<LogEntry> getActorsBenethPlayersFeet();

};

}

#endif // ENGINE_H
