#ifndef ENGINE_H
#define ENGINE_H

#include <libtcod.hpp>
#include <singleton.h>
#include <colored_string.h>
#include <window_manager.h>

namespace amarlon {

class Configuration;
class Map;
class Actor;
class SpellGateway;
class World;
class CommandExecutor;
class MapGateway;
class TileDB;
class ActorDB;

typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<SpellGateway> SpellGatewayPtr;
typedef std::shared_ptr<World> WorldPtr;
typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;
typedef std::shared_ptr<TileDB> TileDBPtr;
typedef std::shared_ptr<ActorDB> ActorDBPtr;

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
  void processInput(TCOD_key_t& key);

  gui::Gui&           getGui() const;
  gui::WindowManager& getWindowManager() const;

  World&        getWorld()        const;
  TileDB&       getTileDB()       const;
  ActorDB&      getActorDB()      const;
  SpellGateway& getSpellGateway() const;

  ActorPtr getPlayer() const;

private:
  gui::GuiPtr _gui;
  CommandExecutorPtr _cmdExecutor;
  gui::WindowManagerPtr _windowManager;
  Configuration* _config;

  WorldPtr _world;
  SpellGatewayPtr _spellGateway;
  TileDBPtr _tileDB;
  ActorDBPtr _actorsDB;

  ActorPtr _player;

  void updateAis();
  std::vector<ColoredString> getActorsBenethPlayersFeet();
  void initializeWorld();

};

}

#endif // ENGINE_H
