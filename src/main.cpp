#include <iostream>
#include <stdexcept>
#include <engine.h>
#include <map.h>
#include <gui.h>
#include <message_box.h>
#include <configuration.h>
#include <game_timer.h>

using namespace std;

int main()
{
  try
  {
    amarlon::Configuration cfg;
    if (!cfg.load("config.cfg")) throw std::runtime_error("Missing configuration file [config.cfg]!");

    amarlon::Engine::instance().init(&cfg);

    TCODConsole::root->setCustomFont(cfg.getFont(),TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(amarlon::Engine::screenWidth,
                          amarlon::Engine::screenHeight,
                          "Amarlon",
                          false,
                          TCOD_RENDERER_SDL);

    TCODConsole::root->setFullscreen( std::stol(cfg.get("fullscreen")) );
    TCODMouse::showCursor(false);
    amarlon::Engine::instance().gui().message(":: Welcome to Amarlon! ::", TCODColor::sky);

    amarlon::Engine::instance().timer().start();

    TCOD_key_t lastKey;
    while ( !TCODConsole::isWindowClosed() )
    {
      try
      {
        TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL, true);        
        if ( lastKey.vk == TCODK_SPACE )
        {
          if ( amarlon::Engine::instance().timer().isRunning() )
          {
            amarlon::Engine::instance().timer().pause();
          }
          else
          {
            amarlon::Engine::instance().timer().resume();
          }
        }

        amarlon::Engine::instance().processKey(lastKey);

      }
      catch(std::exception& e)
      {
        amarlon::gui::msgBox("Fatal error:\n"+std::string(e.what()),
                             amarlon::gui::MsgType::Error);
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

