#include "CmdPick.h"
#include <Engine.h>
#include <World/Map.h>
#include <Actor/Actor.h>
#include <Gui/pick_up_window.h>
#include <functional>

namespace amarlon {

CmdPick::CmdPick(Engine* engine)
  : Command(engine)
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

  Container& container = _engine->currentMap()->getActorsContainer(x, y);

  gui::PickUpWindow pickupWin(*executor, container, [](Actor* a){ return a->afPickable(); });

  pickupWin.show();
}

}
