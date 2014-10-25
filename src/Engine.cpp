#include "Engine.h"
#include "World/Map.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include <algorithm>
#include "Utils/Messenger.h"

namespace amarlon {

int Engine::FovRadius = 20;

Engine::Engine()
  : _console(TCODConsole::root)
  , _gui(nullptr)
{
}

Engine::~Engine()
{
  delete _gui;
}

void Engine::init()
{
  //temp init
  Map::Tiles.loadTiles("../amarlon/tiles.xml");
  Actor::DB.loadActors("../amarlon/actors.xml");
  Map::Gateway.loadMaps("../amarlon/maps.xml");

  _gui = new Gui;

  setCurrentMap( Map::Gateway.fetch(MapId::GameStart) );

  Actor::Player = new Actor(ActorType::Player, 42, 28);

  Messenger::message()->setGui(_gui);
}

void Engine::update()
{
  render();
  updateAis();
  getConsole()->flush();
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
    _gui->render();   
    _gui->renderViewPanel(getActorsBenethPlayersFeet());
  }

  _console->putChar(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getChar());
  _console->setCharForeground(Actor::Player->getX(), Actor::Player->getY(), Actor::Player->getColor());
}

void Engine::updateAis()
{
  if (_currentMap != nullptr)
  {
    std::for_each(_currentMap->actors().begin(), _currentMap->actors().end(), [&](Actor* a)
    {
      if (a->afAi()) a->afAi()->update(_currentMap);
    });
  }
}

void Engine::processKey(TCOD_key_t &key)
{
  CommandExecutor::execute(key, this, Actor::Player);
}

Map *Engine::currentMap() const
{
  return _currentMap;
}

void Engine::setCurrentMap(Map *currentMap)
{
  _currentMap = currentMap;
}
TCODConsole *Engine::getConsole() const
{
  return _console;
}

void Engine::setConsole(TCODConsole *console)
{
  _console = console;
}
Gui *Engine::getGui() const
{
  return _gui;
}

void Engine::setGui(Gui *gui)
{
  _gui = gui;
}

std::vector<LogEntry> Engine::getActorsBenethPlayersFeet()
{
  std::vector<Actor*> actorsOnTile = _currentMap->getActors(Actor::Player->getX(),
                                                            Actor::Player->getY(),
                                                            [&](Actor* a) -> bool
                                                            {
                                                              return a != Actor::Player;
                                                            });

  TCODColor itemViewColor = TCODColor::darkLime;
  std::vector< LogEntry > items;

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

    items.push_back( LogEntry( entryMsg, itemViewColor ) );
  });

  return items;
}

}
