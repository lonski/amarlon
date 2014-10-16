#include "CmdMove.h"
#include "Utils/Utils.h"

CmdMoveOrAttack::CmdMoveOrAttack()
{
}

bool CmdMoveOrAttack::accept(TCOD_key_t &key, Map* map, Actor* executor)
{
  int dx(0), dy(0);
  bool accepted = handleDirectionKey(key, dx, dy);

  if ( accepted )
  {
    int targetX = executor->getX() + dx;
    int targetY = executor->getY() + dy;
    bool blocked = map->isBlocked(targetX, targetY);

    if ( !blocked )
    {
      executor->move(dx, dy);
    }
    else
    {
      std::vector<Actor*> toAttack = map->getActors(targetX, targetY, [&](Actor* a) -> bool
      {
        return a->afFighter() && a->afFighter()->isAlive();
      });

      //attack
      if (!toAttack.empty() && executor->afFighter() )
      {
        assert(toAttack.size() == 1);
        Actor* enemy = toAttack[0];
        executor->afFighter()->attack(enemy);
      }
    }
  }

  return accepted;
}
