#include "cmd_put_into.h"
#include <engine.h>
#include <map.h>
#include <actor.h>

#include <utils.h>
#include <direction_selector.h>
#include <single_neighbour_selector.h>
#include <pick_up_window.h>
#include <message_box.h>
#include <inventory.h>

namespace amarlon {

bool CmdPutInto::accept(const TCOD_key_t& key)
{
  return key.vk == TCODK_CHAR && key.c == 'p';
}

int CmdPutInto::execute()
{
  int turns = 0;
  ActorPtr target = SingleNeighbourSelector("Select a container to put into...")
                    .select()
                    .firstActor();

  if ( target != nullptr && target->hasFeature<Inventory>())
  {
    OpenablePtr openable = target->getFeature<Openable>();
    if ( openable && openable->isClosed() )
    {
      gui::msgBox("Cannot put into " + target->getName() + " - it is closed.", gui::MsgType::Warning);
    }
    else
    {
      auto afterPutIntoAction =
      [&](const std::string& item, int amount)
      {
        target->notify(Event(EventId::Actor_Put,{{"putter","Player"},
                                                 {"container",target->getName()},
                                                 {"count", std::to_string(amount)},
                                                 {"item", tolowers(item)}}));
      };

      auto containerFullAction =
      [&target](const std::string& item)
      {
        gui::msgBox("Cannot put "+item+" into "+tolowers(target->getName())+":#Not enough space!",
                    gui::MsgType::Error);
      };

      Engine::instance().getWindowManager()
                        .getWindow<gui::PickUpWindow>()
                        .setPicker(target)
                        .setSource( [](){ return Engine::instance().getPlayer()->getFeature<Inventory>()->items(); })
                        .setRemoveAction([&](ActorPtr a){Engine::instance().getPlayer()->getFeature<Inventory>()->remove(a);})
                        .setAfterPickupAction( afterPutIntoAction )
                        .setInventoryFullAction( containerFullAction )
                        .setWindowTitle("Select item to put")
                        .show();
    }
    ++turns;
  }
  else if ( target )
  {
    gui::msgBox("You cannot put anything into "+tolowers(target->getName())+".",
                gui::MsgType::Error);
  }
  return turns;
}

}

