#include "Engine.h"
#include "World/Map.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include <algorithm>
#include "Utils/Messenger.h"
#include "Gui/Widget/panel.h"
#include "Gui/Widget/bar.h"

namespace amarlon {

int Engine::FovRadius = 20;

Engine::Engine()
  : _gui(nullptr)
{
}

Engine::~Engine()
{
  delete _gui;
}

void Engine::init()
{
  _cmdExecutor.reset( new CommandExecutor );
  _windowManager.reset( new gui::WindowManager );

  //temp init
  Map::Tiles.loadTiles("tiles.xml");
  Actor::DB.loadActors("actors.xml");
  Map::Gateway.loadMaps("maps.xml");

  _gui = new gui::Gui;

  setCurrentMap( Map::Gateway.fetch(MapId::GameStart) );

  Actor::Player = new Actor(ActorType::Player, 42, 28);

  Messenger::message()->setGui(_gui);
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
