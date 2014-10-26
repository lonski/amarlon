#ifndef ENGINE_H
#define ENGINE_H

#include "Utils/colored_string.h"
#include <libtcod.hpp>
#include "CommandExecutor.h"

namespace amarlon {

class Map;
class Actor;

namespace gui {
  class Gui;
}

class Engine
{
public:
  static int FovRadius;

  Engine();
  ~Engine();

  void init();
  void render();
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

  void updateAis();
  std::vector<ColoredString> getActorsBenethPlayersFeet();

};

}

#endif // ENGINE_H
