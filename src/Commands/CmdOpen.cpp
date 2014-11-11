#include "CmdOpen.h"
#include <iostream>
#include <utils/utils.h>
#include <utils/item_picker.h>
#include <algorithm>
#include "CmdPick.h"
#include <world/map.h>
#include <engine.h>
#include <utils/target_selector/single_neighbour_selector.h>

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

  Actor* target = SingleNeighbourSelector("Select object to open...")
                    .selectFirst(executor, &map);

  if ( target && target->afOpenable() )
  {
    if ( target->afOpenable()->open(executor) )
    {
      map.updateActorCell(target);
    }
  }
}

}
