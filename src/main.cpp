#include <iostream>
#include "engine.h"
#include "World/map.h"

using namespace std;

int main()
{
  const int screenWidth = 100;
  const int screenHeight = 60;

  TCODConsole::initRoot(screenWidth,screenHeight,"Amarlon",false);

  Engine engine;
  Map::Gateway.loadMaps("d:/maps_saved.xml");
  engine.setCurrentMap( Map::Gateway.fetch(MapId::GameStart) );

  while ( !TCODConsole::isWindowClosed() )
  {
    engine.render();
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,NULL,NULL);
    TCODConsole::flush();
  }

  return 0;
}

