#include "cmd_pick.h"
#include <functional>
#include "engine.h"
#include "world/map.h"
#include "actor/actor.h"
#include "gui/window/pick_up_window.h"
#include "gui/message_box.h"
#include "utils/messenger.h"

namespace amarlon {

CmdPick::CmdPick()
{
}

bool CmdPick::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == ',' );
}

void CmdPick::execute()
{
  int x( Actor::Player->getX() );
  int y( Actor::Player->getY() );

  Container& container = Engine::instance().currentMap().getActorsContainer(x, y);

  auto afterPickupAction =
  [](const std::string& item, int amount)
  {
    Messenger::message()->actorPicked(Actor::Player->getName(), item, amount);
  };

  auto inventoryFullAction =
  [](const std::string& item)
  {
    gui::msgBox("Cannot pickup "+item+":\nInventory is full!", gui::MsgType::Error);
  };

  Engine::instance().windowManager()
                    .getWindow<gui::PickUpWindow>()
                    .setPicker(Actor::Player)
                    .setContainer(&container)
                    .setFilterFunction( [](Actor* a){ return a->getFeature<Pickable>(); } )
                    .setAfterPickupAction( afterPickupAction )
                    .setInventoryFullAction( inventoryFullAction )
                    .show();

}

}
