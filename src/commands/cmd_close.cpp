#include "cmd_close.h"
#include <algorithm>
#include "actor/actor.h"
#include "world/map.h"
#include "engine.h"
#include "utils/utils.h"
#include "utils/target_selector/single_neighbour_selector.h"
#include "gui/message_box.h"

namespace amarlon {

CmdClose::CmdClose()
{
}

bool CmdClose::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'c' );
}

void CmdClose::execute()
{
  Map& map = Engine::instance().currentMap();

  std::vector<Actor*> actorsOnTile = SingleNeighbourSelector("Select object to close...")
                                       .select();

  auto openableIter = std::find_if(actorsOnTile.begin(), actorsOnTile.end(),
                                   [](Actor* a)
                                   { return a->getFeature<Openable>(); });

  Actor* toClose = openableIter != actorsOnTile.end() ? *openableIter : nullptr;

  if ( toClose != nullptr)
  {
    if ( actorsOnTile.size() == 1 )
    {
      if (toClose->getFeature<Openable>()->close(Actor::Player)) map.updateActorCell(toClose);
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
