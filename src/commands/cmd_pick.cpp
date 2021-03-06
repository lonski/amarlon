#include "cmd_pick.h"
#include <engine.h>
#include <map.h>
#include <actor.h>
#include <pick_up_window.h>
#include <message_box.h>

#include <actor_container.h>

namespace amarlon {

CmdPick::CmdPick()
{
}

bool CmdPick::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_CHAR && key.c == ',' );
}

int CmdPick::execute()
{
  int turns = 0;
  int x( Engine::instance().getPlayer()->getX() );
  int y( Engine::instance().getPlayer()->getY() );

  MapPtr map = Engine::instance().getPlayer()->getMap();
  if ( map )
  {
    auto inventoryFullAction =
    [](const std::string& item)
    {
      gui::msgBox("Cannot pickup "+item+":#Inventory is full!", gui::MsgType::Error);
    };

    Engine::instance().getWindowManager()
                      .getWindow<gui::PickUpWindow>()
                      .setPicker(Engine::instance().getPlayer())
                      .setSource( [&](){ return map->getActors( x, y, [](ActorPtr a){ return a->getFeature<Pickable>() != nullptr;}); } )
                      .setRemoveAction([&](ActorPtr a){ map->removeActor(a); })
                      .setInventoryFullAction( inventoryFullAction )
                      .show();
    ++turns;
  }
  return turns;
}

}

