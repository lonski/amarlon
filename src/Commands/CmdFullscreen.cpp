#include "CmdFullscreen.h"
#include "Engine.h"

CmdFullscreen::CmdFullscreen()
{
}

bool CmdFullscreen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_F12 );
}

void CmdFullscreen::execute(Engine* engine, Actor*)
{
  TCODConsole::root->setFullscreen( !engine->getConsole()->isFullscreen() );
}
