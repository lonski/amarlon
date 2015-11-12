#include "cmd_game_menu.h"
#include <engine.h>

namespace amarlon {

CmdGameMenu::CmdGameMenu()
{
}

bool CmdGameMenu::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_ESCAPE );
}

int CmdGameMenu::execute()
{
  Engine::instance().showGameMenu();
  return 0;
}

}
