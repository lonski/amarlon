#include "attack_action.h"
#include <actor.h>
#include <dices.h>


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
    performer->setVisible(true);

    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = _target->getFeature<Character>();

    if ( attacker && attacked && attacker != attacked)
    {
      success = true;
      bool hit = false;
      int dieRoll = dices::roll( dices::D20 );

      if ( dieRoll != dices::NATURAL_ONE ) //natural one is always a failure
      {
        int attackRoll = dieRoll + attacker->getMeleeAttackBonus();

        if ( ( dieRoll == dices::NATURAL_TWENTY ) || //natural 20 is always a hit
             ( attackRoll >= attacked->getArmorClass()) ) //hit success
        {
          hit = true;
          attacked->takeDamage(attacker->getDamage(), _performer);
        }
      }

      if ( !hit )
      {
        _performer->notify(Event(EventId::Actor_Missed,{{"target",_target->getName()}}));
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

