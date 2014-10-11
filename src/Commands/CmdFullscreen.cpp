#include "CmdFullscreen.h"

CmdFullscreen::CmdFullscreen()
{
}

bool CmdFullscreen::accept(TCOD_key_t &key, Map*, Actor*)
{
  bool accepted = ( key.vk == TCODK_F12 );

  if (accepted)
  {
    TCODConsole::root->setFullscreen( !TCODConsole::root->isFullscreen() );
  }

  return accepted;
}
