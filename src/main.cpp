#include <iostream>
#include <stdexcept>
#include <engine.h>

int main()
{
  try
  {
    amarlon::Engine::instance().prologue();
    amarlon::Engine::instance().initializeConsole();
    amarlon::Engine::instance().showGameMenu();

    while ( !TCODConsole::isWindowClosed() && !amarlon::Engine::instance().isQuiting() )
    {
      amarlon::Engine::instance().render();
      TCODConsole::root->flush();
      int turns = amarlon::Engine::instance().processInput();
      while ( turns-- ) amarlon::Engine::instance().update();
    }

    amarlon::Engine::instance().epilogue();
  }
  catch(std::exception &e)
  {
    std::cout << "\nError: " << e.what() << std::endl;
    amarlon::Engine::instance().epilogue();
  }
  catch(...)
  {
    std::cout << "\nUnknown error has occured.";
    amarlon::Engine::instance().epilogue();
  }

  return 0;
}

