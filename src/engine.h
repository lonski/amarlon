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
class SpellDB;
class World;
class SystemCommandExecutor;
class MapDB;
class TileDB;
class ActorDB;
class SkillDB;
class RpgDB;
class Messenger;
class Module;
class TreasureGenerator;

namespace lua_api {
  class LuaState;
  typedef std::shared_ptr<LuaState> LuaStatePtr;
}

typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<SpellDB> SpellDBPtr;
typedef std::shared_ptr<SkillDB> SkillDBPtr;
typedef std::shared_ptr<RpgDB> RpgDBPtr;
typedef std::shared_ptr<World> WorldPtr;
typedef std::shared_ptr<SystemCommandExecutor> SystemCommandExecutorPtr;
typedef std::shared_ptr<TileDB> TileDBPtr;
typedef std::shared_ptr<ActorDB> ActorDBPtr;
typedef std::shared_ptr<Configuration> ConfigurationPtr;
typedef std::shared_ptr<Messenger> MessengerPtr;
typedef std::shared_ptr<Module> ModulePtr;
typedef std::shared_ptr<TreasureGenerator> TreasureGeneratorPtr;

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
  static int FovRadiusTorch;

  ~Engine();

  void prologue();
  void initializeConsole();
  void epilogue();

  void enterGame(const std::string &savedGameFn = "");
  void showGameMenu();
  void quit();
  /**
   * @brief A flag to quit the game was set.
   */
  bool isQuiting() const;
  /**
   * @brief The game was already started and is running.
   */
  bool isRunning() const;

  void render();
  void flush();
  void update();
  void processInput();
  void loadModule(const Module& module);

  gui::Gui&           getGui() const;
  gui::WindowManager& getWindowManager() const;

  World&             getWorld()             const;
  TileDB&            getTileDB()            const;
  ActorDB&           getActorDB()           const;
  SpellDB&           getSpellDB()           const;
  SkillDB&           getSkillDB()           const;
  RpgDB&             getRpgDB()             const;
  Messenger&         getMessenger()         const;
  lua_api::LuaState& getLuaState()          const;
  Module&            getModule()            const;
  TreasureGenerator& getTreasureGenerator() const;

  TCODConsole* getConsole();

  const ActorPtr getPlayer() const;
  TCOD_key_t getLastInput() const;
  void setLastInput(TCOD_key_t key);

private:
  gui::GuiPtr _gui;
  SystemCommandExecutorPtr _sysCmdExecutor;
  gui::WindowManagerPtr _windowManager;
  ConfigurationPtr _config;

  WorldPtr _world;
  SpellDBPtr _spellDB;
  TileDBPtr _tileDB;
  ActorDBPtr _actorsDB;
  SkillDBPtr _skillsDB;
  RpgDBPtr _rpgDB;
  MessengerPtr _messenger;
  lua_api::LuaStatePtr _luaState;
  ModulePtr _module;
  TreasureGeneratorPtr _treasureGenerator;

  bool _quit;
  bool _running;
  TCOD_key_t _lastInput;
  TCODConsole* _console;

  std::vector<ColoredString> getActorsBenethPlayersFeet();
  int updatePlayerControlledActors(MapPtr map);
  void updateNonPlayerControlledActors(MapPtr map);
  void configureLogger();

};

}

#endif // ENGINE_H
