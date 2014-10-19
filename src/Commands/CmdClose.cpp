#include "CmdClose.h"

CmdClose::CmdClose()
{
}

bool CmdClose::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'c' );
}

void CmdClose::execute(Map *map, Actor *executor)
{
  int x = executor->getX();
  int y = executor->getY();

  int dx(0), dy(0);

  _dSelector.select(dx, dy);

  Actor* target = map->getFirstActor(x+dx, y+dy);
  if ( target && target->afOpenable() )
  {
    if ( target->afOpenable()->close(executor) )
    {
      map->updateActorCell(target);
    }
  }
}
