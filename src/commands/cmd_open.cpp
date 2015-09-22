#include "cmd_open.h"
#include <iostream>
#include <algorithm>
#include <cmd_pick.h>
#include <utils.h>
#include <single_neighbour_selector.h>
#include <gui/message_box.h>
#include <open_action.h>

namespace amarlon {

CmdOpen::CmdOpen()
{
}

bool CmdOpen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'o' );
}

int CmdOpen::execute()
{
  int turns = 0;
  std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr a)->bool{ return a->getFeature<Openable>() != nullptr; };

  ActorPtr toOpen = SingleNeighbourSelector("Select object to open...")
                    .select(filterFun)
                    .firstActor();

  if ( toOpen != nullptr)
  {
    Engine::instance().getPlayer()->performAction( std::make_shared<OpenAction>(toOpen) );
    ++turns;
  }
  else
  {
    gui::msgBox("Nothing to open there.", gui::MsgType::Warning);
  }
  return turns;
}

}

