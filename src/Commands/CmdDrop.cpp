#include "CmdDrop.h"
#include "Utils/InventoryManager.h"
#include "World/Map.h"
#include "Engine.h"
#include <algorithm>

namespace amarlon {

CmdDrop::CmdDrop()
{
}

bool CmdDrop::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'd' );
}

void CmdDrop::execute(Engine *engine, Actor *executor)
{
  InventoryManager inv(executor);
  std::vector<Actor*> items = inv.pickItems();

  std::for_each(items.begin(), items.end(), [&](Actor* a)
  {
    a->setX( executor->getX() );
    a->setY( executor->getY() );
    engine->currentMap()->addActor(a);
  });
}

}
