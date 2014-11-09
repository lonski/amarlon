#include "CmdClose.h"
#include "Actor/Actor.h"
#include "World/Map.h"
#include "Engine.h"

namespace amarlon {

CmdClose::CmdClose()
{
}

bool CmdClose::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'c' );
}

void CmdClose::execute(Actor *executor)
{
  Map& map = Engine::instance().currentMap();
  int x = executor->getX();
  int y = executor->getY();

  int dx(0), dy(0);

  _dSelector.select(dx, dy);

  Actor* target = map.getFirstActor(x+dx, y+dy);
  if ( target && target->afOpenable() )
  {
    if ( target->afOpenable()->close(executor) )
    {
      map.updateActorCell(target);
    }
  }
}

}
