#include "console_freezer.h"

namespace amarlon {

ConsoleFreezer::ConsoleFreezer(TCODConsole *console)
  : _console(console)
{
}

void ConsoleFreezer::freeze()
{
  _console->saveApf("data/tmp");
}

void ConsoleFreezer::restore()
{
  _console->loadApf("data/tmp");
}

}
