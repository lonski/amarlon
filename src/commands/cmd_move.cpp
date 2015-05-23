#include "cmd_move.h"
#include <utils.h>
#include <map.h>
#include <engine.h>
#include <move_action.h>
#include <attack_action.h>

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
  //if MoveAction failed then path is blocked
  if ( !Actor::Player->performAction( std::make_shared<MoveAction>(_dx, _dy) ) )
  {
    Actor::Player->performAction( std::make_shared<AttackAction>( getActorToAttack() ));
  }
}

ActorPtr CmdMoveOrAttack::getActorToAttack()
{
  int targetX = Actor::Player->getX() + _dx;
  int targetY = Actor::Player->getY() + _dy;
  MapPtr map = Engine::instance().currentMap();

  std::function<bool (amarlon::ActorPtr)> filterFun = [&](amarlon::ActorPtr a)->bool
  {
    return a->hasFeature<Fighter>() && a->getFeature<Fighter>()->isAlive();
  };
  std::vector<ActorPtr> toAttack = map->getActors(targetX, targetY, &filterFun);

  return toAttack.empty() ? ActorPtr() : toAttack.front();
}

void CmdMoveOrAttack::setDirection(int dx, int dy)
{
  if (dx > 0) _dx = 1;
  else if (dx < 0) _dx = -1;

  if (dy > 0) _dy = 1;
  else if (dy < 0) _dy = -1;
}

}
