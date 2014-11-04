#include <iostream>
#include "Utils/glodef.h"
#include "Engine.h"
#include "World/Map.h"
#include "Gui/Gui.h"
#include <Gui/message_box.h>

using namespace std;

int main()
{
  try
  {
    TCODConsole::root->setCustomFont("terminal.png");
    TCODConsole::initRoot(amarlon::gloScreenWidth,amarlon::gloScreenHeight,"Amarlon",false, TCOD_RENDERER_SDL);

    TCODMouse::showCursor(false);
    TCOD_key_t lastKey;

    amarlon::Engine engine;
    engine.init();

    engine.getGui()->message(":: Welcome to Amarlon! ::", TCODColor::sky);

    while ( !TCODConsole::isWindowClosed() )
    {
      try
      {
        engine.update();
        engine.render();

        TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL, true);
        engine.processKey(lastKey);
      }
      catch(std::exception& e)
      {
        amarlon::gui::msgError("Fatal error:\n"+std::string(e.what()));
      }
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

