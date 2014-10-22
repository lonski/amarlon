#include <iostream>
#include "Utils/glodef.h"
#include "Engine.h"
#include "World/Map.h"
#include "Gui/Gui.h"

using namespace std;

int main()
{
  try
  {
    TCODConsole::root->setCustomFont("../amarlon/terminal.png");
    TCODConsole::initRoot(gloScreenWidth,gloScreenHeight,"Amarlon",false, TCOD_RENDERER_SDL);

    TCODMouse::showCursor(false);
    TCOD_key_t lastKey;

    Engine engine;
    engine.init();

    engine.getGui()->message(":: Welcome to Amarlon! ::", TCODColor::sky);

    while ( !TCODConsole::isWindowClosed() )
    {
      engine.update();

      TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL, true);
      engine.processKey(lastKey);
    }
  }
  catch(std::exception &e)
  {
    std::cout << "\nError: " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "\nUnknown error has occured.";
  }

  return 0;
}

