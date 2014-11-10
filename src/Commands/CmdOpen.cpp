#include "CmdOpen.h"
#include <iostream>
#include <utils/utils.h>
#include <utils/item_picker.h>
#include <algorithm>
#include "CmdPick.h"
#include <world/map.h>
#include <engine.h>

namespace amarlon {

CmdOpen::CmdOpen()
{
}

bool CmdOpen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'o' );
}

void CmdOpen::execute(Actor *executor)
{
  Map& map = Engine::instance().currentMap();
  int x = executor->getX();
  int y = executor->getY();

  int dx(0), dy(0);

  _dSelector.select(dx, dy);

  Actor* target = map.getFirstActor(x+dx, y+dy);

  if ( target && target->afOpenable() )
  {
    if ( target->afOpenable()->open(executor) )
    {
      map.updateActorCell(target);
    }
  }
}

}
