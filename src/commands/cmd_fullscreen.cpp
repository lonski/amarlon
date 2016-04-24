#include "cmd_fullscreen.h"
#include <engine.h>

namespace amarlon {

CmdFullscreen::CmdFullscreen()
{
}

bool CmdFullscreen::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_F12 );
}

int CmdFullscreen::execute()
{
  TCODConsole* console = Engine::instance().getConsole();

  if ( console )
    console->setFullscreen( !console->isFullscreen() );

  return 0;
}

}

