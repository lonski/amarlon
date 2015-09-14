#include <iostream>
#include <stdexcept>
#include <engine.h>

int main()
{
  try
  {
    amarlon::Engine::instance().prologue();

    while ( !TCODConsole::isWindowClosed() )
    {
      amarlon::Engine::instance().render();
      amarlon::Engine::instance().processInput();
      amarlon::Engine::instance().update();
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

