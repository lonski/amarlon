#include "CmdPick.h"
#include <engine.h>
#include <world/map.h>
#include <Actor/Actor.h>
#include <gui/window/pick_up_window.h>
#include <functional>
#include <utils/messenger.h>
#include <gui/message_box.h>

namespace amarlon {

CmdPick::CmdPick()
{
}

bool CmdPick::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == ',' );
}

void CmdPick::execute(Actor *executor)
{
  int x( executor->getX() );
  int y( executor->getY() );

  Container& container = Engine::instance().currentMap().getActorsContainer(x, y);

  auto afterPickupAction =
  [&executor](const std::string& item, int amount)
  {
    Messenger::message()->actorPicked(executor->getName(), item, amount);
  };

  auto inventoryFullAction =
  [](const std::string& item)
  {
    gui::msgBox("Cannot pickup "+item+":\nInventory is full!", gui::MsgType::Error);
  };

  Engine::instance().windowManager()
                    .getWindow<gui::PickUpWindow>()
                    .setPicker(executor)
                    .setContainer(&container)
                    .setFilterFunction( [](Actor* a){ return a->afPickable(); } )
                    .setAfterPickupAction( afterPickupAction )
                    .setInventoryFullAction( inventoryFullAction )
                    .show();

}

}
