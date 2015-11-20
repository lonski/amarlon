#include "monster_move_action.h"
#include <actor.h>
#include <character.h>
#include <engine.h>

namespace amarlon {

MonsterMoveAction::MonsterMoveAction(int dx, int dy)
  : MoveAction(dx, dy)
  , _moveCost(0)
{
  CharacterPtr player = Engine::instance().getPlayer()->getFeature<Character>();
  _moveCost = player ? player->getSpeed() : 40;
}

MonsterMoveAction::~MonsterMoveAction()
{
}

ActorActionResult MonsterMoveAction::perform(ActorPtr performer)
{
  _performer = performer;
  ActorActionResult r = ActorActionResult::Nok;

  if ( _performer )
  {
    CharacterPtr mob = _performer->getFeature<Character>();
    if ( mob )
    {
      if ( mob->getMovePoints() < _moveCost ) //normal move, otherwise it is 'extra' move
      {
        mob->setMovePoints( mob->getMovePoints() + mob->getSpeed() );
      }

      while ( mob->getMovePoints() >= _moveCost )
      {
        r = doMove(mob);
      }

    }
  }

  return r;
}

ActorActionResult MonsterMoveAction::doMove(CharacterPtr mob)
{
  mob->setMovePoints( mob->getMovePoints() - _moveCost );

  ActorActionResult result = MoveAction::perform(_performer);

  AiPtr ai = _performer->getFeature<Ai>();
  if ( ai && mob->getMovePoints() >= _moveCost ) //check if extra move
  {
    ai->update();
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

