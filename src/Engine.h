#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include <Utils/singleton.h>
#include "Utils/colored_string.h"
#include "CommandExecutor.h"
#include <Gui/Window/window_manager.h>

namespace amarlon {

class Map;
class Actor;

typedef std::shared_ptr<Map> MapPtr;

namespace gui {
  class Gui;
}

class Engine : public Singleton<Engine>
{
  friend class Singleton;
  Engine();

public:
  constexpr static const int consoleWidth = 100;
  constexpr static const int consoleHeight = 60;
  constexpr static const int rightPanelWidth = 20;
  constexpr static const int bottomPanelHeight = 15;
  constexpr static const int screenWidth = 100 + rightPanelWidth;
  constexpr static const int screenHeight = 60 + bottomPanelHeight;

  static int FovRadius;

  ~Engine();

  void init();
  void render();
  void update();
  void processKey(TCOD_key_t& key);

  gui::Gui& gui() const;
  gui::WindowManager& windowManager() const;

  Map& currentMap() const;
  void setCurrentMap(MapPtr currentMap);

private:
  MapPtr _currentMap;
  gui::Gui* _gui;
  CommandExecutorPtr _cmdExecutor;
  gui::WindowManagerPtr _windowManager;

  void updateAis();
  std::vector<ColoredString> getActorsBenethPlayersFeet();

};

}

#endif // ENGINE_H
