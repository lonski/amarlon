#include "cmd_put_into.h"
#include <engine.h>
#include <world/map.h>
#include <Actor/Actor.h>
#include <gui/window/pick_up_window.h>
#include <utils/messenger.h>
#include <utils/utils.h>
#include <gui/message_box.h>
#include <utils/target_selector/single_neighbour_selector.h>
#include <iostream>

namespace amarlon {

bool CmdPutInto::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == 'p';
}

void CmdPutInto::execute(Actor *executor)
{
  Actor* target = SingleNeighbourSelector()
                    .selectFirst(executor,
                                 &Engine::instance().currentMap());

  if ( target && target->afContainer() )
  {
    auto afterPutIntoAction =
    [&](const std::string& item, int amount)
    {
      Messenger::message()->actorPutInto(executor->getName(), target->getName(), item, amount);
    };

    auto containerFullAction =
    [&target](const std::string& item)
    {
      gui::msgError("Cannot put "+item+" into "+tolowers(target->getName())+":\nNot enough space!");
    };

    Engine::instance().windowManager()
                      .getWindow<gui::PickUpWindow>()
                      .setPicker(target)
                      .setContainer(Actor::Player->afContainer())
                      .setAfterPickupAction( afterPutIntoAction )
                      .setInventoryFullAction( containerFullAction )
                      .setWindowTitle("Select item to put")
                      .show();
  }
  else if ( target )
  {
    gui::msgError("You cannot put anything into "+tolowers(target->getName())+".");
  }

}

}
