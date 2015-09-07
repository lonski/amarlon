#include <engine.h>
#include <algorithm>
#include <map.h>
#include <actor.h>
#include <gui.h>
#include <spell.h>
#include <utils/configuration.h>
#include <utils/messenger.h>

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

void Engine::prologue(Configuration* cfg)
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
  Map::Gateway.load( cfg->get("maps_file") );
  Spell::Gateway.load( cfg->get("spells_file") );

  Messenger::message()->setGui(_gui.get());

  getWorld().load( cfg->get("save_file") );
  getWorld().changeMap( MapId::GameStart );

  if ( Actor::Player == nullptr )
  {
    Actor::Player = Actor::create(ActorType::Player, 42, 28);
    getWorld().getCurrentMap()->addActor( Actor::Player );
  }
}

void Engine::epilogue()
{
  getWorld().store( _config->get("save_file") );
}

void Engine::update()
{
  updateAis();
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
      _gui->setHpBar(Actor::Player->getFeature<Character>()->getHitPoints(), Actor::Player->getFeature<Character>()->getMaxHitPoints());

    _gui->setViewList(getActorsBenethPlayersFeet());
    _gui->render();
  }

  TCODConsole::root->putChar(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getChar());
  TCODConsole::root->setCharForeground(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getColor());
}

void Engine::updateAis()
{
  MapPtr map = getWorld().getCurrentMap();
  if ( map )
  {    
    std::function<bool(ActorPtr)> filter = [](ActorPtr a)->bool{ return a->hasFeature<Ai>();};    
    auto ais = map->getActors( &filter );
    for ( ActorPtr actor : ais )
    {
      actor->getFeature<Ai>()->update();
    }
  }
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
