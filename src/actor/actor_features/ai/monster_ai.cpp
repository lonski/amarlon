#include "monster_ai.h"
#include <cmath>
#include <map.h>
#include <actor.h>
#include <amarlon_except.h>
#include <move_action.h>
#include <attack_action.h>

namespace amarlon {

int MonsterAi::TrackingTurns = 5;

MonsterAi::MonsterAi()
  : _map(nullptr)
  , _trackCount(0)
  , _cX(0)
  , _cY(0)
{
}

ActorFeaturePtr MonsterAi::clone()
{
  MonsterAiPtr cloned( new MonsterAi );
  cloned->_map = _map;
  cloned->_trackCount = _trackCount;
  cloned->_cX = _cX;
  cloned->_cY = _cY;

  return cloned;
}

bool MonsterAi::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  MonsterAiPtr crhs = std::dynamic_pointer_cast<MonsterAi>(rhs);

  if (crhs)
  {
    equal = true;
  }

  return equal;
}

void MonsterAi::update(MapPtr map)
{
  _map = map;
  if (getOwner().lock()->isAlive() && _map)
  {
    updatePosition();

    if (_map->isInFov(_cX, _cY))
    {
      _trackCount = TrackingTurns;
    }
    else
    {
      --_trackCount;
    }

    if ( _trackCount > 0)
    {
      huntPlayer();
    }
  }
}

void MonsterAi::huntPlayer()
{
  int dx = Actor::Player->getX() - _cX;
  int dy = Actor::Player->getY() - _cY;
  int stepDx = (dx > 0 ? 1:-1);
  int stepDy = (dy > 0 ? 1:-1);

  ActorPtr monster = getOwner().lock();
  float distance = sqrtf(dx*dx + dy*dy);

  if ( distance >= 2 )
  {
    dx = (int)(round(dx/distance));
    dy = (int)(round(dy/distance));


    if ( !_map->isBlocked(_cX+dx, _cY+dy) )
    {      
      monster->performAction( std::make_shared<MoveAction>(dx, dy) );
    }
    else if ( !_map->isBlocked(_cX+stepDx, _cY) )
    {
      monster->performAction( std::make_shared<MoveAction>(stepDx, 0) );
    }
    else if ( !_map->isBlocked(_cX, _cY+stepDy) )
    {
      monster->performAction( std::make_shared<MoveAction>(0, stepDy) );
    }
  }
  else if ( getOwner().lock()->hasFeature<Fighter>() )
  {
    monster->performAction( std::make_shared<AttackAction>(Actor::Player) );
  }
}

void MonsterAi::updatePosition()
{
  _cX = getOwner().lock()->getX();
  _cY = getOwner().lock()->getY();
}

}
