#include "Engine.h"
#include "World/Map.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include <algorithm>
#include "Utils/Messenger.h"
#include "Gui/Widget/panel.h"
#include "Gui/Widget/bar.h"

#include "Gui/InventoryWindow/inventory_window.h"

namespace amarlon {

int Engine::FovRadius = 20;

Engine::Engine()
  : _console(TCODConsole::root)
  , _gui(nullptr)
  , cmdExecutor( new CommandExecutor(this) )
{
}

Engine::~Engine()
{
  delete _gui;
}

void Engine::init()
{
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
  _console->clear();
  if (_currentMap != nullptr)
  {
    _currentMap->computeFov(Actor::Player->getX(), Actor::Player->getY(), FovRadius);
    _currentMap->render(_console);
  }

  if (_gui)
  {
    _gui->setPlayerName(Actor::Player->getName());

    if ( Actor::Player->isAlive() )
      _gui->setHpBar(Actor::Player->afFighter()->getHp(), Actor::Player->afFighter()->getMaxHp());

    _gui->setViewList(getActorsBenethPlayersFeet());
    _gui->render();
  }

  _console->putChar(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getChar());
  _console->setCharForeground(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getColor());

  getConsole()->flush();
}

void Engine::updateAis()
{
/*
 *
 *  !!! TODO !!! Make a function "Apply unction to actors" on map, and then pass only function to execute
 *
 */
//  if (_currentMap != nullptr)
//  {
//    std::for_each(_currentMap->actors().begin(), _currentMap->actors().end(), [&](Actor* a)
//    {
//      if (a->afAi()) a->afAi()->update( currentMap() );
//    });
//  }
}

void Engine::processKey(TCOD_key_t &key)
{
  cmdExecutor->execute(key, Actor::Player);
}

Map* Engine::currentMap() const
{
  return _currentMap.get();
}

void Engine::setCurrentMap(MapPtr currentMap)
{
  _currentMap = currentMap;
}
TCODConsole* Engine::getConsole() const
{
  return _console;
}

void Engine::setConsole(TCODConsole *console)
{
  _console = console;
}
gui::Gui* Engine::getGui() const
{
  return _gui;
}

void Engine::setGui(gui::Gui *gui)
{
  _gui = gui;
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
