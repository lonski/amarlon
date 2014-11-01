#include "CmdFullscreen.h"
#include "Engine.h"

namespace amarlon {

CmdFullscreen::CmdFullscreen(Engine *engine)
  : Command(engine)
{
}

bool CmdFullscreen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_F12 );
}

void CmdFullscreen::execute(Actor*)
{
  TCODConsole::root->setFullscreen( !_engine->getConsole()->isFullscreen() );
}

}
