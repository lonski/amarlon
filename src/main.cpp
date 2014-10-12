#include <iostream>
#include "Utils/glodef.h"
#include "engine.h"
#include "World/map.h"
#include "Gui/gui.h"

using namespace std;

int main()
{

  TCODConsole::initRoot(gloScreenWidth,gloScreenHeight,"Amarlon",false, TCOD_RENDERER_SDL);

  TCODMouse::showCursor(false);
  TCOD_key_t lastKey;

  Engine engine;
  Gui::Root.message(":: Welcome to Amarlon! ::", TCODColor::sky);

  engine.init();

  while ( !TCODConsole::isWindowClosed() )
  {
    engine.render();
    Gui::Root.render();
    engine.updateAis();
    TCODConsole::flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL, true);
    engine.processKey(lastKey);
  }

  return 0;
}

