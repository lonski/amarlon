#include "cmd_close.h"
#include <algorithm>
#include <actor.h>
#include <map.h>
#include <utils.h>
#include <single_neighbour_selector.h>
#include <message_box.h>
#include <close_action.h>

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
  std::vector<ActorPtr> actorsOnTile = SingleNeighbourSelector("Select object to close...")
                                       .select();

  auto openableIter = std::find_if(actorsOnTile.begin(), actorsOnTile.end(),
                                   [](ActorPtr a)
                                   { return a->getFeature<Openable>(); });

  ActorPtr toClose = openableIter != actorsOnTile.end() ? *openableIter : nullptr;

  if ( toClose != nullptr)
  {
    if ( actorsOnTile.size() == 1 )
    {
      Actor::Player->performAction( std::make_shared<CloseAction>(toClose) );
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
