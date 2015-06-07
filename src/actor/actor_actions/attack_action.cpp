#include "attack_action.h"
#include <actor.h>
#include <dices.h>
#include <messenger.h>

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
  bool success = false;

  if ( _performer && _target )
  {
    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = _target->getFeature<Character>();

    if ( attacker && attacked )
    {
      success = true;
      bool hit = false;
      int dieRoll = dices::roll( dices::D20 );

      if ( dieRoll != dices::NATURAL_ONE ) //natural one is always a failure
      {
        if ( ( dieRoll == dices::NATURAL_TWENTY ) || //natural 20 is always a hit
             ( dieRoll + attacker->getMeleeAttackBonus() >= attacked->getArmorClass()) ) //hit success
        {
          hit = true;
          int damage = attacker->rollMeleeDamage();
          Messenger::message()->actorHit(_performer, _target, damage);
          attacked->modifyHitPoints( -1 * damage );
        }
      }

      if ( !hit )
      {
        Messenger::message()->actorMissed(_performer, _target);
      }
    }
  }

  return success;
}

ActorActionUPtr AttackAction::clone()
{
  AttackActionUPtr cloned = std::make_unique<AttackAction>(_target);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}
