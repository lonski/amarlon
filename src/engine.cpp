#include <engine.h>
#include <algorithm>
#include <map.h>
#include <actor.h>
#include <gui.h>
#include <utils/configuration.h>
#include <utils/messenger.h>
#include <game_timer.h>
#include <window_manager.h>


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
  _timer = new GameTimer;
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

  Messenger::message()->setGui(_gui.get());

  Actor::Player = Actor::create(ActorType::Player, 42, 28);

  getWorld().changeMap( MapId::GameStart );
  getWorld().getCurrentMap()->addActor( Actor::Player );
}

void Engine::update()
{
  MapPtr map = getWorld().getCurrentMap();
  if ( map )
  {
    for ( ActorPtr a : map->getActors() )
    {
      a->tick();
    }
  }
}

void Engine::render()
{
  TCODConsole::root->clear();
  MapPtr map = getWorld().getCurrentMap();

  if ( map )
  {
    map->computeFov(Actor::Player->getX(), Actor::Player->getY(), FovRadius);
    map->render(TCODConsole::root);
  }

  if (_gui)
  {
    _gui->setPlayerName(Actor::Player->getName());

    if ( Actor::Player->isAlive() )
      _gui->setHpBar(Actor::Player->getFeature<Fighter>()->getHp(), Actor::Player->getFeature<Fighter>()->getMaxHp());

    _gui->setViewList(getActorsBenethPlayersFeet());
    _gui->render();
  }

  //TCODConsole::root->putChar(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getChar());
  //TCODConsole::root->setCharForeground(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getColor());

//  auto visibleWindows = windowManager().getWindows( [](gui::WindowPtr w){ return w->isVisible(); } );
//  for ( gui::WindowPtr w : visibleWindows )
//  {
//    w->render(*TCODConsole::root);
//  }  
}

void Engine::processKey(TCOD_key_t &key)
{
  _cmdExecutor->execute(key);
}

gui::Gui& Engine::gui() const
{
  return *_gui;
}

gui::WindowManager& Engine::windowManager() const
{
  return *_windowManager;
}

GameTimer& Engine::timer()
{
  return *_timer;
}

World& Engine::getWorld()
{
  return _world;
}

std::vector<ColoredString> Engine::getActorsBenethPlayersFeet()
{
  std::vector< ColoredString > items;
  MapPtr map = getWorld().getCurrentMap();

  if ( map )
  {
    std::function<bool(amarlon::ActorPtr)> filterFun = [&](ActorPtr a) -> bool
    {
      return a != Actor::Player;
    };

    std::vector<ActorPtr> actorsOnTile = map->getActors(Actor::Player->getX(), Actor::Player->getY(), &filterFun);

    for ( ActorPtr actor : actorsOnTile )
    {
      std::string msg = actor->getName();

      PickablePtr pickable = actor->getFeature<Pickable>();
      if ( pickable && pickable->getAmount() > 1 )
      {
        msg = msg + " (" + std::to_string(pickable->getAmount()) + ")";
      }

      items.push_back( ColoredString( msg, TCODColor::darkLime ) );
    }
  }

  return items;
}

}
