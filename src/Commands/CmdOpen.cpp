#include "CmdOpen.h"
#include <iostream>
#include <utils/utils.h>
#include <utils/item_picker.h>
#include <algorithm>
#include "CmdPick.h"
#include <world/map.h>
#include <engine.h>
#include <utils/target_selector/single_neighbour_selector.h>
#include <gui/message_box.h>

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
                    .selectFirst(executor,
                                 &map,
                                 [](Actor* a)->bool{ return a->afOpenable();});

  if ( target != nullptr)
  {
    if ( target->afOpenable()->open(executor) )
    {
      map.updateActorCell(target);
    }
  }
  else
  {
    gui::msgBox("Nothing to open there.", gui::MsgType::Warning);
  }
}

}
