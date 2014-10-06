#include "CmdMove.h"

CmdMoveOrAttack::CmdMoveOrAttack()
{
}

bool CmdMoveOrAttack::accept(TCOD_key_t &key, Actor* executor, Map* map)
{
  bool accepted = true;

  int dx(0), dy(0);
  switch(key.vk)
  {
    case TCODK_KP2: dy++; break;
    case TCODK_KP8: dy--; break;
    case TCODK_KP4: dx--; break;
    case TCODK_KP6: dx++; break;
    case TCODK_KP7: dx--; dy--; break;
    case TCODK_KP9: dx++; dy--; break;
    case TCODK_KP1: dx--; dy++; break;
    case TCODK_KP3: dx++; dy++; break;
    default: accepted = false; break;
  }

  if ( accepted )
  {
    bool blocked = map->isBlocked(executor->getX() + dx, executor->getY() + dy);

    if ( !blocked )
    {
      executor->move(dx, dy);
    }
    else
    {
      //TODO: attack
    }
  }

  return accepted;
}
