#include <iostream>
#include <stdexcept>
#include <engine.h>
#include <logger.h>

int main()
{
  try
  {
    amarlon::Engine::instance().prologue();
    amarlon::Engine::instance().initializeConsole();
    amarlon::Engine::instance().showGameMenu();

    LOG(amarlon::LogType::Info, amarlon::LogFeature::General, "Amarlon engine started.");

    while ( !TCODConsole::isWindowClosed() && !amarlon::Engine::instance().isQuiting() )
    {
      amarlon::Engine::instance().render();
      amarlon::Engine::instance().flush();
      amarlon::Engine::instance().processInput();
      amarlon::Engine::instance().update();
    }

    amarlon::Engine::instance().epilogue();
  }
  catch(std::exception &e)
  {
    LOG(amarlon::LogType::Error,
        amarlon::LogFeature::General,
        e.what());

    amarlon::Engine::instance().epilogue();
  }
  catch(...)
  {
    LOG(amarlon::LogType::Error,
        amarlon::LogFeature::General,
        "Unknown error has occured.");

    amarlon::Engine::instance().epilogue();
  }

  return 0;
}

