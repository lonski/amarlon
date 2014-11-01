#include "console_freezer.h"

namespace amarlon {

ConsoleFreezer::ConsoleFreezer(TCODConsole *console)
  : _console(console)
{
}

void ConsoleFreezer::freeze()
{
  _console->saveApf("tmp");
}

void ConsoleFreezer::restore()
{
  _console->loadApf("tmp");
}

}
