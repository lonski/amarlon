#include "shot_action.h"
#include <actor.h>
#include <dices.h>

namespace amarlon {

ShotAction::ShotAction(ActorPtr target)
  : _target(target)
{
}

ShotAction::~ShotAction()
{
}

bool ShotAction::perform(ActorPtr performer)
{
  _performer = performer;
  bool success = false;

  if ( isTargetCorrect() && isReadyToShot() )
  {
    //TODO
  }

  return success;
}

int ShotAction::calculateAttackBonusModifier()
{
  const int CLOSE_RANGE = 2;

  enum ModifierByRange
  {
    CLOSE  = -5,
    SHORT  = 1,
    MEDIUM = 0,
    LONG   = -2
  };

  int modifier = CLOSE;

  int distance = calculateDistance(_performer, _target);
  if ( distance > CLOSE_RANGE )
  {
    float relativeDistance = distance / getWeapon()->getRange();

    if ( relativeDistance < 0.5 )
      modifier = SHORT;
    else if ( relativeDistance > 1.5 )
      modifier = LONG;
    else
      modifier = MEDIUM;
  }

  return modifier;
}

bool ShotAction::isTargetCorrect()
{
  if ( _performer && _target )
  {
    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = _target->getFeature<Character>();

    return attacker && attacked && attacker != attacked;
  }
  return false;
}

bool ShotAction::isReadyToShot()
{
  PickablePtr weapon = getWeapon();
  PickablePtr amunition = getAmunition();

  return weapon    &&
         amunition &&
         amunition->getAmount() > 0 &&
         amunition->getItemType().amunition == weapon->getItemType().amunition;
}

PickablePtr ShotAction::getWeapon()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  ActorPtr weaponActor = wearer->equipped( ItemSlotType::MainHand );
  return weaponActor ? weaponActor->getFeature<Pickable>() : nullptr;
}

PickablePtr ShotAction::getAmunition()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  ActorPtr amunitionActor = wearer->equipped( ItemSlotType::Amunition );
  return amunitionActor ? amunitionActor->getFeature<Pickable>() : nullptr;
}

ActorActionUPtr ShotAction::clone()
{
  ShotActionUPtr cloned = std::make_unique<ShotAction>(_target);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}

