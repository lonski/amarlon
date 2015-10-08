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
class SpellDatabase;
class World;
class CommandExecutor;
class MapGateway;
class TileDatabase;
class ActorDB;
class Messenger;

namespace lua_api {
  class LuaState;
  typedef std::shared_ptr<LuaState> LuaStatePtr;
}

typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<SpellDatabase> SpellDatabasePtr;
typedef std::shared_ptr<World> WorldPtr;
typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;
typedef std::shared_ptr<TileDatabase> TileDatabasePtr;
typedef std::shared_ptr<ActorDB> ActorDBPtr;
typedef std::shared_ptr<Configuration> ConfigurationPtr;
typedef std::shared_ptr<Messenger> MessengerPtr;

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

  void prologue();
  void initializeConsole();
  void epilogue();

  void render();
  void update();
  int processInput();

  gui::Gui&           getGui() const;
  gui::WindowManager& getWindowManager() const;

  World&             getWorld()     const;
  TileDatabase&            getTileDatabase()    const;
  ActorDB&           getActorDB()   const;
  SpellDatabase&           getSpellDatabase()   const;
  Messenger&         getMessenger() const;
  lua_api::LuaState& getLuaState()  const;

  ActorPtr getPlayer() const;

private:
  gui::GuiPtr _gui;
  CommandExecutorPtr _cmdExecutor;
  gui::WindowManagerPtr _windowManager;
  ConfigurationPtr _config;

  WorldPtr _world;
  SpellDatabasePtr _SpellDatabase;
  TileDatabasePtr _tileDB;
  ActorDBPtr _actorsDB;
  MessengerPtr _messenger;
  lua_api::LuaStatePtr _luaState;

  ActorPtr _player;

  std::vector<ColoredString> getActorsBenethPlayersFeet();
  void initializeWorld();

};

}

#endif // ENGINE_H
