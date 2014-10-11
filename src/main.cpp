#include <iostream>
#include "engine.h"
#include "World/map.h"

using namespace std;

int main()
{
  const int screenWidth = 100;
  const int screenHeight = 60;

  TCODConsole::initRoot(screenWidth,screenHeight,"Amarlon",false, TCOD_RENDERER_SDL);
  TCOD_key_t lastKey;

  Engine engine;
  engine.init();

  while ( !TCODConsole::isWindowClosed() )
  {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
    engine.processKey(lastKey);
    engine.render();
    TCODConsole::flush();
  }

  return 0;
}

