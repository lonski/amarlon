#include <iostream>
#include <stdexcept>
#include <engine.h>
#include <map.h>
#include <gui.h>
#include <message_box.h>
#include <configuration.h>

using namespace std;

int main()
{
  try
  {
    amarlon::Configuration cfg;
    if (!cfg.load("config.cfg")) throw std::runtime_error("Missing configuration file [config.cfg]!");

    amarlon::Engine::instance().prologue(&cfg);

    TCODConsole::root->setCustomFont(cfg.getFont(),TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(amarlon::Engine::screenWidth,
                          amarlon::Engine::screenHeight,
                          "Amarlon",
                          false,
                          TCOD_RENDERER_SDL);

    TCODConsole::root->setFullscreen( std::stol(cfg.get("fullscreen")) );
    TCODMouse::showCursor(true);
    amarlon::Engine::instance().getGui().message(":: Welcome to Amarlon! ::", TCODColor::sky);

    TCOD_key_t lastKey;
    while ( !TCODConsole::isWindowClosed() )
    {
      try
      {
        amarlon::Engine::instance().update();        
        amarlon::Engine::instance().render();
        TCODConsole::root->flush();

        TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL, true);
        amarlon::Engine::instance().processInput(lastKey);
      }
      catch(std::exception& e)
      {
        amarlon::gui::msgBox("Fatal error:\n"+std::string(e.what()),
                             amarlon::gui::MsgType::Error);
      }
    }

    amarlon::Engine::instance().epilogue();

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

