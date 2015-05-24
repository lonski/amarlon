#include "attack_action.h"
#include <actor.h>

namespace amarlon {

AttackAction::AttackAction(ActorPtr target)
  : _target(target)
{
}

AttackAction::~AttackAction()
{
}

bool AttackAction::perform(ActorPtr performer)
{
  _performer = performer;
  bool attacked = false;

  if ( _performer && _target )
  {
    FighterPtr fighter = performer->getFeature<Fighter>();
    if ( fighter )
    {
      fighter->attack(_target);
    }
  }

  return attacked;
}

ActorActionUPtr AttackAction::clone()
{
  AttackActionUPtr cloned = std::make_unique<AttackAction>(_target);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}
