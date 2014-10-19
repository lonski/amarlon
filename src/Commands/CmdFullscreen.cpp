#include "CmdFullscreen.h"

CmdFullscreen::CmdFullscreen()
{
}

bool CmdFullscreen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_F12 );
}

void CmdFullscreen::execute(Map*, Actor*)
{
  TCODConsole::root->setFullscreen( !TCODConsole::root->isFullscreen() );
}
