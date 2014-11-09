#include "Engine.h"
#include "World/Map.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include <algorithm>
#include <utils/messenger.h>
#include "Gui/Widget/panel.h"
#include "Gui/Widget/bar.h"
#include <utils/configuration.h>

namespace amarlon {

int Engine::FovRadius = 20;
int Engine::consoleWidth = 100;
int Engine::consoleHeight = 60;
int Engine::rightPanelWidth = 20;
int Engine::bottomPanelHeight = 15;
int Engine::screenWidth = 100 + Engine::rightPanelWidth;
int Engine::screenHeight = 60 + Engine::bottomPanelHeight;

Engine::Engine()
  : _config(nullptr)
{
}

Engine::~Engine()
{
}

void Engine::init(Configuration* cfg)
{
  _config = cfg;
  _cmdExecutor.reset( new CommandExecutor );
  _windowManager.reset( new gui::WindowManager );
  _gui.reset( new gui::Gui );

  Engine::consoleWidth      = std::stol( _config->get("console_width") );
  Engine::consoleHeight     = std::stol( _config->get("console_height") );
  Engine::rightPanelWidth   = std::stol( _config->get("right_panel_width") );
  Engine::bottomPanelHeight = std::stol( _config->get("bottom_panel_height") );;
  Engine::screenWidth       = Engine::consoleWidth + Engine::rightPanelWidth;
  Engine::screenHeight      = Engine::consoleHeight + Engine::bottomPanelHeight;

  Map::Tiles.loadTiles( cfg->get("tiles_file") );
  Actor::DB.loadActors( cfg->get("actors_file") );
  Map::Gateway.loadMaps( cfg->get("maps_file") );

  Actor::Player = new Actor(ActorType::Player, 42, 28);
  Messenger::message()->setGui(_gui.get());

  setCurrentMap( Map::Gateway.fetch(MapId::GameStart) );
}

void Engine::update()
{
  updateAis();
}

void Engine::render()
{
  TCODConsole::root->clear();
  if (_currentMap != nullptr)
  {
    _currentMap->computeFov(Actor::Player->getX(), Actor::Player->getY(), FovRadius);
    _currentMap->render(TCODConsole::root);
  }

  if (_gui)
  {
    _gui->setPlayerName(Actor::Player->getName());

    if ( Actor::Player->isAlive() )
      _gui->setHpBar(Actor::Player->afFighter()->getHp(), Actor::Player->afFighter()->getMaxHp());

    _gui->setViewList(getActorsBenethPlayersFeet());
    _gui->render();
  }

  TCODConsole::root->putChar(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getChar());
  TCODConsole::root->setCharForeground(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getColor());

  TCODConsole::root->flush();
}

void Engine::updateAis()
{
  if (_currentMap != nullptr)
  {
    std::function<bool(Actor*)> filter = [](Actor* a)->bool{ return a->afAi();};
    std::vector<Actor*> ais = currentMap().getActors( &filter );

    std::for_each( ais.begin(), ais.end(), [&](Actor* a){a->afAi()->update( &currentMap() );});
  }
}

void Engine::processKey(TCOD_key_t &key)
{
  _cmdExecutor->execute(key, Actor::Player);
}

Map &Engine::currentMap() const
{
  return *_currentMap;
}

void Engine::setCurrentMap(MapPtr currentMap)
{
  _currentMap = currentMap;
}

gui::Gui& Engine::gui() const
{
  return *_gui;
}

gui::WindowManager& Engine::windowManager() const
{
  return *_windowManager;
}

std::vector<ColoredString> Engine::getActorsBenethPlayersFeet()
{
  std::vector<Actor*> actorsOnTile = _currentMap->getActors(Actor::Player->getX(),
                                                            Actor::Player->getY(),
                                                            [&](Actor* a) -> bool
                                                            {
                                                              return a != Actor::Player;
                                                            });

  TCODColor itemViewColor = TCODColor::darkLime;
  std::vector< ColoredString > items;

  std::for_each(actorsOnTile.begin(), actorsOnTile.end(), [&](Actor* a)
  {
    int amount = 1;
    if ( a->afPickable() )
    {
      amount = a->afPickable()->getAmount();
    }

    std::string entryMsg = a->getName();

    if (amount > 1)
      entryMsg = entryMsg + " (" + std::to_string(amount) + ")";

    items.push_back( ColoredString( entryMsg, itemViewColor ) );
  });

  return items;
}

}
