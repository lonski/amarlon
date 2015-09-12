#include "cmd_put_into.h"
#include <engine.h>
#include <map.h>
#include <actor.h>
#include <messenger.h>
#include <utils.h>
#include <direction_selector.h>
#include <single_neighbour_selector.h>
#include <pick_up_window.h>
#include <message_box.h>
#include <inventory.h>

namespace amarlon {

bool CmdPutInto::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == 'p';
}

void CmdPutInto::execute()
{
  ActorPtr target = SingleNeighbourSelector("Select a container to put into...")
                    .select()
                    .firstActor();

  if ( target != nullptr && target->hasFeature<Inventory>())
  {
    auto afterPutIntoAction =
    [&](const std::string& item, int amount)
    {
      Messenger::message()->actorPutInto(Engine::instance().getPlayer()->getName(), target->getName(), item, amount);
    };

    auto containerFullAction =
    [&target](const std::string& item)
    {
      gui::msgBox("Cannot put "+item+" into "+tolowers(target->getName())+":\nNot enough space!",
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
  else if ( target )
  {
    gui::msgBox("You cannot put anything into "+tolowers(target->getName())+".",
                gui::MsgType::Error);
  }

}

}
