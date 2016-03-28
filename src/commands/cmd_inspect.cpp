#include "cmd_inspect.h"
#include <message_box.h>
#include <single_neighbour_selector.h>
#include <engine.h>
#include <window_manager.h>
#include <pick_up_window.h>

namespace amarlon {

CmdInspect::CmdInspect()
{
}

bool CmdInspect::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'i' );
}

int CmdInspect::execute()
{
  int turns = 0;
  std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr a)->bool{ return a->getFeature<Inventory>() != nullptr; };

  ActorPtr toInspect = SingleNeighbourSelector("Select object to inspect...")
                     . select(filterFun)
                     . firstActor();

  if ( toInspect != nullptr)
  {
    InventoryPtr inv = toInspect->getFeature<Inventory>();
    if ( inv->size() > 0 )
    {
      //Check if actor is openned
      OpenablePtr openable = toInspect->getFeature<Openable>();
      if ( openable && openable->isClosed() )
      {
        gui::msgBox("Cannot inspect " + toInspect->getName() + " - it is closed.", gui::MsgType::Warning);
      }
      else
      {
        auto& window = Engine::instance().getWindowManager().getWindow<gui::PickUpWindow>();
        window.setSource( [&inv](){ return inv->items(); } );
        window.setPicker(Engine::instance().getPlayer());
        window.setInventoryFullAction( [](const std::string& item){ gui::msgBox("Cannot pickup "+item+":#Inventory is full!", gui::MsgType::Error); } );
        window.setRemoveAction( [&](ActorPtr a){ return inv->remove(a); } );
        window.show();

      }
    }
    else
    {
      gui::msgBox(toInspect->getName() + " is empty.", gui::MsgType::Warning);
    }
    ++turns;
  }
  else
  {
    gui::msgBox("Nothing to inspect there.", gui::MsgType::Warning);
  }

  return turns;
}

}
