#include "cmd_open.h"
#include <iostream>
#include <algorithm>
#include <engine.h>
#include "cmd_pick.h"
#include "utils/utils.h"
#include "utils/item_picker.h"
#include "utils/target_selector/single_neighbour_selector.h"
#include "world/map.h"
#include "gui/message_box.h"

namespace amarlon {

CmdOpen::CmdOpen()
{
}

bool CmdOpen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'o' );
}

void CmdOpen::execute()
{
  Map& map = Engine::instance().currentMap();
  std::function<bool (amarlon::Actor*)> filterFun = [](Actor* a)->bool{ return a->getFeature<Openable>(); };
  Actor* target = SingleNeighbourSelector("Select object to open...")
                    .selectFirst(&filterFun);

  if ( target != nullptr)
  {
    if ( target->getFeature<Openable>()->open(Actor::Player) )
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
