#include <iostream>
#include "Engine.h"
#include "World/Map.h"
#include "Gui/Gui.h"
#include <Gui/message_box.h>
#include <Utils/singleton.h>

using namespace std;

int main()
{

  try
  {
    TCODConsole::root->setCustomFont("prestige12.png",TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GRAYSCALE);

    TCODConsole::initRoot(amarlon::Engine::screenWidth,
                          amarlon::Engine::screenHeight,
                          "Amarlon",
                          false,
                          TCOD_RENDERER_SDL);

    TCODMouse::showCursor(false);
    TCOD_key_t lastKey;

    amarlon::Engine::instance().init();

    amarlon::Engine::instance().gui().message(":: Welcome to Amarlon! ::", TCODColor::sky);

    while ( !TCODConsole::isWindowClosed() )
    {
      try
      {
        amarlon::Engine::instance().update();
        amarlon::Engine::instance().render();

        TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL, true);
        amarlon::Engine::instance().processKey(lastKey);
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

