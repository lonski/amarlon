#include "CmdClose.h"
#include "Actor/Actor.h"
#include <world/map.h>
#include <engine.h>
#include <utils/target_selector/single_neighbour_selector.h>
#include <algorithm>
#include <gui/message_box.h>
#include <utils/utils.h>

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

  std::vector<Actor*> actorsOnTile = SingleNeighbourSelector("Select object to close...")
                                       .select(executor, &map);

  auto openableIter = std::find_if(actorsOnTile.begin(), actorsOnTile.end(),
                                   [](Actor* a)
                                   { return a->afOpenable(); });

  Actor* toClose = openableIter != actorsOnTile.end() ? *openableIter : nullptr;

  if ( toClose )
  {
    if ( actorsOnTile.size() == 1 && toClose->afOpenable()->close(executor))
    {
      map.updateActorCell(toClose);
    }
    else
    {
      gui::msgBox("Cannot close " + tolowers(toClose->getName())+":\n"
                  "It is blocked!",
                  gui::MsgType::Warning);
    }
  }
  else
  {
    gui::msgBox("Nothing to close there.", gui::MsgType::Warning);
  }
}

}
