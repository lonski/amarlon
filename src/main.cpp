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
  TCOD_key_t lastKey;

  //temp init
  Map::Gateway.loadMaps("d:/maps_saved.xml");
  engine.setCurrentMap( Map::Gateway.fetch(MapId::GameStart) );

  while ( !TCODConsole::isWindowClosed() )
  {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
    engine.processKey(lastKey);
    engine.render();
    TCODConsole::flush();
  }

  return 0;
}

