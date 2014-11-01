#ifndef CONSOLE_FREEZER_H
#define CONSOLE_FREEZER_H

#include <libtcod.hpp>

namespace amarlon {

class ConsoleFreezer
{
public:
  ConsoleFreezer(TCODConsole* console);
  void freeze();
  void restore();

private:
  TCODConsole* _console;
};

}

#endif // CONSOLE_FREEZER_H
