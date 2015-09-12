#include "cmd_move.h"
#include <utils.h>
#include <map.h>
#include <move_action.h>
#include <attack_action.h>
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
  //if MoveAction failed then path is blocked
  if ( !Engine::instance().getPlayer()->performAction( std::make_shared<MoveAction>(_dx, _dy) ) )
  {
    Engine::instance().getPlayer()->performAction( std::make_shared<AttackAction>( getActorToAttack() ));
  }
}

ActorPtr CmdMoveOrAttack::getActorToAttack()
{
  ActorPtr toAttack;
  MapPtr map = Engine::instance().getPlayer()->getMap();

  if ( map )
  {
    int targetX = Engine::instance().getPlayer()->getX() + _dx;
    int targetY = Engine::instance().getPlayer()->getY() + _dy;

    std::function<bool (amarlon::ActorPtr)> filterFun = [&](amarlon::ActorPtr a)->bool
    {
      return a->hasFeature<Character>() && a->getFeature<Character>()->isAlive();
    };

    auto targets = map->getActors(targetX, targetY, filterFun);
    if ( !targets.empty() )
    {
      toAttack = targets.front();
    }
  }

  return toAttack;
}

void CmdMoveOrAttack::setDirection(int dx, int dy)
{
  if (dx > 0) _dx = 1;
  else if (dx < 0) _dx = -1;

  if (dy > 0) _dy = 1;
  else if (dy < 0) _dy = -1;
}

}
