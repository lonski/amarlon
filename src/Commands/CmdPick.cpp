#include "CmdPick.h"
#include <Engine.h>
#include <World/Map.h>
#include <Actor/Actor.h>
#include <Gui/Window/pick_up_window.h>
#include <functional>

namespace amarlon {

CmdPick::CmdPick()
{
}

bool CmdPick::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == ',' );
}

void CmdPick::execute(Actor *executor)
{
  int x( executor->getX() );
  int y( executor->getY() );

  Container& container = Engine::instance().currentMap().getActorsContainer(x, y);

  Engine::instance().windowManager()
                    .getWindow<gui::PickUpWindow>()
                    .setPicker(executor)
                    .setContainer(&container)
                    .setFilterFunction( [](Actor* a){ return a->afPickable(); } )
                    .show();
}

}
