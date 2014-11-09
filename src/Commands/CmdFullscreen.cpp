#include "CmdFullscreen.h"
#include "Engine.h"

namespace amarlon {

CmdFullscreen::CmdFullscreen()
{
}

bool CmdFullscreen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_F12 );
}

void CmdFullscreen::execute(Actor*)
{
  TCODConsole::root->setFullscreen( !TCODConsole::root->isFullscreen() );
}

}
