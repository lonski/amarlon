#include "cmd_pick.h"
#include <engine.h>
#include <map.h>
#include <actor.h>
#include <pick_up_window.h>
#include <message_box.h>
#include <messenger.h>

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

  MapPtr map = Actor::Player->getMap();
  if ( map )
  {
    ContainerPtr container = map->getActorsContainer(x, y);

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
                      .setContainer(container)
                      .setFilterFunction( [](ActorPtr a){ return a->getFeature<Pickable>() != nullptr; } )
                      .setAfterPickupAction( afterPickupAction )
                      .setInventoryFullAction( inventoryFullAction )
                      .show();
  }

}

}
