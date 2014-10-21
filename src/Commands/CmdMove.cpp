#include "CmdMove.h"
#include "Utils/Utils.h"
#include "World/Map.h"
#include "Engine.h"

CmdMoveOrAttack::CmdMoveOrAttack()
  : _dx(0)
  , _dy(0)
{
}

bool CmdMoveOrAttack::accept(TCOD_key_t &key)
{
  _dx = 0;
  _dy = 0;
  return handleDirectionKey(key, _dx, _dy);
}

void CmdMoveOrAttack::execute(Engine *engine, Actor *executor)
{
  Map* map = engine->currentMap();
  int targetX = executor->getX() + _dx;
  int targetY = executor->getY() + _dy;
  bool blocked = map->isBlocked(targetX, targetY);

  if ( !blocked )
  {
    executor->move(_dx, _dy);
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

void CmdMoveOrAttack::setDirection(int dx, int dy)
{
  if (dx > 0) _dx = 1;
  else if (dx < 0) _dx = -1;

  if (dy > 0) _dy = 1;
  else if (dy < 0) _dy = -1;
}
