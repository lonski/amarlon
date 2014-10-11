#include "CmdDrop.h"
#include "Utils/InventoryManager.h"
#include <algorithm>

CmdDrop::CmdDrop()
{
}

bool CmdDrop::accept(TCOD_key_t &key, Map *map, Actor *executor)
{
  bool accepted = ( key.vk == TCODK_CHAR && key.c == 'd' );

  if (accepted)
  {
    InventoryManager inv(executor);
    std::vector<Actor*> items = inv.pickItems();

    std::for_each(items.begin(), items.end(), [&](Actor* a)
    {
      a->setX( executor->getX() );
      a->setY( executor->getY() );
      map->addActor(a);
    });
  }

  return accepted;
}
