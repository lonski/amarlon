#include "cmd_put_into.h"
#include <iostream>
#include "engine.h"
#include "world/map.h"
#include "actor/actor.h"
#include "utils/messenger.h"
#include "utils/utils.h"
#include "utils/direction_selector.h"
#include "utils/target_selector/single_neighbour_selector.h"
#include "gui/window/pick_up_window.h"
#include "gui/message_box.h"

namespace amarlon {

bool CmdPutInto::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == 'p';
}

void CmdPutInto::execute()
{
  ActorPtr target = SingleNeighbourSelector("Select a container to put into...")
                    .selectFirst();

  if ( target != nullptr && target->hasFeature<Container>())
  {
    auto afterPutIntoAction =
    [&](const std::string& item, int amount)
    {
      Messenger::message()->actorPutInto(Actor::Player->getName(), target->getName(), item, amount);
    };

    auto containerFullAction =
    [&target](const std::string& item)
    {
      gui::msgBox("Cannot put "+item+" into "+tolowers(target->getName())+":\nNot enough space!",
                  gui::MsgType::Error);
    };

    Engine::instance().windowManager()
                      .getWindow<gui::PickUpWindow>()
                      .setPicker(target)
                      .setContainer(Actor::Player->getFeature<Container>())
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
