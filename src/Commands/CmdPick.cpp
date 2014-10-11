#include "CmdPick.h"
#include <Utils/ItemPicker.h>
#include <algorithm>

CmdPick::CmdPick()
{
}

bool CmdPick::accept(TCOD_key_t &key, Map *map, Actor *executor)
{
  bool accepted = ( key.vk == TCODK_CHAR && key.c == ',' );

  if (accepted)
  {
    std::vector<Actor*> items = map->getActors(executor->getX(), executor->getY(),
                                [](Actor* a) -> bool
                                {
                                  return a->afPickable;
                                });

    ItemPicker picker(executor, items);
    items = picker.pick();

    std::for_each(items.begin(), items.end(), [&](Actor* a)
    {
      map->removeActor(a);
    });
  }

  return accepted;
}
