#include "CmdClose.h"
#include "Actor/Actor.h"
#include <world/map.h>
#include <engine.h>
#include <utils/target_selector/single_neighbour_selector.h>

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

  Actor* target = SingleNeighbourSelector("Select object to close...")
                    .selectFirst(executor,
                                 &map);

  if ( target && target->afOpenable() )
  {
    if ( target->afOpenable()->close(executor) )
    {
      map.updateActorCell(target);
    }
  }
}

}
