#include "cmd_close.h"
#include <algorithm>
#include <actor.h>
#include <map.h>
#include <utils.h>
#include <single_neighbour_selector.h>
#include <message_box.h>
#include <close_action.h>
#include <engine.h>

namespace amarlon {

CmdClose::CmdClose()
{
}

bool CmdClose::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'c' );
}

int CmdClose::execute()
{
  int turns = 0;
  Target target = SingleNeighbourSelector("Select object to close...")
                                         .select();

  auto openableIter = std::find_if(target.actors.begin(), target.actors.end(),
                                   [](ActorPtr a)
                                   { return a->getFeature<Openable>(); });

  ActorPtr toClose = openableIter != target.actors.end() ? *openableIter : nullptr;

  if ( toClose != nullptr)
  {
    if ( target.actors.size() == 1 )
    {
      OpenablePtr openable = toClose->getFeature<Openable>();
      if ( openable )
      {
        Engine::instance().getPlayer()->performAction( std::make_shared<CloseAction>(toClose) );
      }
      else
      {
        gui::msgBox(toClose->getName() + " is not closable.", gui::MsgType::Warning);
      }
    }
    else
    {
      gui::msgBox("Cannot close " + tolowers(toClose->getName())+":#"
                  "It is blocked!",
                  gui::MsgType::Warning);
    }
    ++turns;
  }
  else
  {
    gui::msgBox("Nothing to close there.", gui::MsgType::Warning);
  }
  return turns;
}

}

