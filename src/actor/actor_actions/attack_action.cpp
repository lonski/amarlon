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

}
