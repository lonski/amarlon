#include <iostream>
#include <stdexcept>
#include <engine.h>

int main()
{
  try
  {
    amarlon::Engine::instance().prologue();
    amarlon::Engine::instance().showGameMenu();

    while ( !TCODConsole::isWindowClosed() && !amarlon::Engine::instance().isQuiting() )
    {
      amarlon::Engine::instance().render();
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

