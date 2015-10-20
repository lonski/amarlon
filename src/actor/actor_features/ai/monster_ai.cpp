#include "monster_ai.h"
#include <cmath>
#include <map.h>
#include <actor.h>
#include <amarlon_except.h>
#include <monster_move_action.h>
#include <attack_action.h>
#include <engine.h>
#include <actor_descriptions.h>

namespace amarlon {

const ActorFeature::Type MonsterAi::featureType = ActorFeature::AI;
int MonsterAi::TrackingTurns = 10;

AiType MonsterAi::getAiType() const
{
  return AiType::MonsterAi;
}

MonsterAi::MonsterAi(AiDescriptionPtr dsc )
  : Ai(dsc)
  , _map(nullptr)
  , _trackCount(0)
  , _cX(0)
  , _cY(0)
{
}

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

  cloneBase(cloned);

  return cloned;
}

bool MonsterAi::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  MonsterAiPtr crhs = std::dynamic_pointer_cast<MonsterAi>(rhs);

  if (crhs)
  {
    equal = true;
  }

  return equal;
}

void MonsterAi::update()
{  
  ActorPtr owner = getOwner().lock();
  if ( owner && canOperate() )
  {
    MapPtr map = owner->getMap();
    if ( map )
    {
      _map = map;
      if (getOwner().lock()->isAlive() && _map)
      {
        updatePosition();

        if (_map->isInFov(_cX, _cY) && Engine::instance().getPlayer()->isVisible())
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
  }
}

bool MonsterAi::isHunting() const
{
  return _trackCount > 0 && getOwner().lock()->isAlive();
}

bool MonsterAi::isHostileTo(ActorPtr actor) const
{
  if ( actor )
  {
    AiPtr ai = actor->getFeature<Ai>();
    //Hostile to all non monsters
    return ai && ai->getAiType() != getAiType();
  }
  return false;
}

bool MonsterAi::isAllyOf(ActorPtr actor) const
{
  //Allied with all other monsters
  return !isHostileTo(actor);
}

void MonsterAi::huntPlayer()
{
  ActorPtr player = Engine::instance().getPlayer();
  ActorPtr monster = getOwner().lock();

  int dx = player->getX() - _cX;
  int dy = player->getY() - _cY;
  int stepDx = (dx > 0 ? 1:-1);
  int stepDy = (dy > 0 ? 1:-1);

  float distance = sqrtf(dx*dx + dy*dy);

  if ( distance >= 2 )
  {
    dx = (int)(round(dx/distance));
    dy = (int)(round(dy/distance));

    if ( !_map->isBlocked(_cX+dx, _cY+dy) )
    {
      monster->performAction( std::make_shared<MonsterMoveAction>(dx, dy) );
    }
    else if ( !_map->isBlocked(_cX+stepDx, _cY) )
    {
      monster->performAction( std::make_shared<MonsterMoveAction>(stepDx, 0) );
    }
    else if ( !_map->isBlocked(_cX, _cY+stepDy) )
    {
      monster->performAction( std::make_shared<MonsterMoveAction>(0, stepDy) );
    }
  }
  else if ( getOwner().lock()->hasFeature<Character>() )
  {
    monster->performAction( std::make_shared<AttackAction>(player) );
  }

}

void MonsterAi::updatePosition()
{
  _cX = getOwner().lock()->getX();
  _cY = getOwner().lock()->getY();
}

}

