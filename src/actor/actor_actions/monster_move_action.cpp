#include "monster_move_action.h"
#include <actor.h>
#include <character.h>
#include <monster.h>

namespace amarlon {

MonsterMoveAction::MonsterMoveAction(int dx, int dy)
  : MoveAction(dx, dy)
  , _moveCost(0)
  , _currentMovePoints(0)
{
  CharacterPtr player = Actor::Player->getFeature<Character>();
  _moveCost = player ? player->getSpeed() : 40;
}

MonsterMoveAction::~MonsterMoveAction()
{
}

bool MonsterMoveAction::perform(ActorPtr performer)
{
  bool result = false;

  if ( performer )
  {
    _performer = performer;

    CharacterPtr mob = performer->getFeature<Character>();
    if ( mob )
    {
      calculateMovePoints(mob);
      result = doMove(mob);
    }
  }

  return result;
}

void MonsterMoveAction::calculateMovePoints(CharacterPtr mob)
{
  _currentMovePoints = mob->getMovePoints();

  if ( _currentMovePoints > 0 ) //last time actor did not moved, continue moving
  {
    _currentMovePoints -= mob->getSpeed();
  }
  else //last time actor did move, and eventually some extra move points left
  {
    _currentMovePoints = _moveCost - ( mob->getSpeed() + std::abs(_currentMovePoints) );
  }

  mob->setMovePoints(_currentMovePoints);
}

bool MonsterMoveAction::doMove(CharacterPtr mob)
{
  bool result = false;

  if ( _currentMovePoints <= 0 ) //ok, we can move
  {
    result = MoveAction::perform(_performer);

    //check if extra move
    AiPtr ai = _performer->getFeature<Ai>();
    if ( -1*_currentMovePoints >= _moveCost && ai)
    {
      mob->setMovePoints( _currentMovePoints + _moveCost + mob->getSpeed()  );
      ai->update();
    }
  }

  return result;
}

ActorActionUPtr MonsterMoveAction::clone()
{
  MonsterMoveActionUPtr cloned = std::make_unique<MonsterMoveAction>(_dx,_dy);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}
