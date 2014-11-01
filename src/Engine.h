#ifndef ENGINE_H
#define ENGINE_H

#include "Utils/colored_string.h"
#include <libtcod.hpp>
#include "CommandExecutor.h"

namespace amarlon {

class Map;
class Actor;

typedef std::shared_ptr<Map> MapPtr;

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
  void setCurrentMap(amarlon::MapPtr currentMap);

  TCODConsole *getConsole() const;
  void setConsole(TCODConsole *getConsole);

  gui::Gui *getGui() const;
  void setGui(gui::Gui *getGui);

private:
  TCODConsole* _console;
  MapPtr _currentMap;
  gui::Gui* _gui;
  CommandExecutorPtr cmdExecutor;

  void updateAis();
  std::vector<ColoredString> getActorsBenethPlayersFeet();

};

}

#endif // ENGINE_H
