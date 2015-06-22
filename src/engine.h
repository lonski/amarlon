#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include <singleton.h>
#include <colored_string.h>
#include <command_executor.h>
#include <window_manager.h>
#include <world.h>

namespace amarlon {

class Configuration;
class Map;
class Actor;

typedef std::shared_ptr<Map> MapPtr;

namespace gui {
  class Gui;
  typedef std::shared_ptr<Gui> GuiPtr;
}

class Engine : public Singleton<Engine>
{
  friend class Singleton;
  Engine();

public:
  static int consoleWidth;
  static int consoleHeight;
  static int rightPanelWidth;
  static int bottomPanelHeight;
  static int screenWidth;
  static int screenHeight;

  static int FovRadius;

  ~Engine();

  void prologue(Configuration *cfg);
  void epilogue();
  void render();
  void update();
  void processKey(TCOD_key_t& key);

  gui::Gui& gui() const;
  gui::WindowManager& windowManager() const;

  World& getWorld();

private:  
  gui::GuiPtr _gui;
  CommandExecutorPtr _cmdExecutor;
  gui::WindowManagerPtr _windowManager;
  Configuration* _config;
  World _world;

  void updateAis();
  std::vector<ColoredString> getActorsBenethPlayersFeet();

};

}

#endif // ENGINE_H
