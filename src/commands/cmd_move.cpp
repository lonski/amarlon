#include "cmd_move.h"
#include <utils/utils.h>
#include <world/map.h>
#include <engine.h>

namespace amarlon {

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

void CmdMoveOrAttack::execute()
{
  Map& map = Engine::instance().currentMap();
  int targetX = Actor::Player->getX() + _dx;
  int targetY = Actor::Player->getY() + _dy;
  bool blocked = map.isBlocked(targetX, targetY);

  if ( !blocked )
  {
    Actor::Player->move(_dx, _dy);
  }
  else
  {
    std::vector<Actor*> toAttack = map.getActors(targetX, targetY, [&](Actor* a) -> bool
    {
      return a->hasFeature<Fighter>() && a->getFeature<Fighter>()->isAlive();
    });

    //attack
    if (!toAttack.empty() && Actor::Player->hasFeature<Fighter>() )
    {
      assert(toAttack.size() == 1);
      Actor* enemy = toAttack[0];
      Actor::Player->getFeature<Fighter>()->attack(enemy);
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

}