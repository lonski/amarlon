#include "range_attack.h"
#include <shot_action.h>
#include <ai.h>
#include <actor.h>

namespace amarlon { namespace state {

RangeAttack::RangeAttack()
{
}

FSMStateType RangeAttack::getType() const
{
  return FSMStateType::ATTACK_RANGE;
}

int RangeAttack::update()
{
  if ( _ai )
  {
    ActorPtr enemy = _ai->getTarget().firstActor();
    ActorPtr me = _ai->getOwner().lock();

    if ( me && enemy )
    {
      me->performAction( std::make_shared<ShotAction>(enemy) );
    }
  }

  return 0;
}

bool RangeAttack::canEnter()
{
  bool canEnter = false;
  if ( _ai && _ai->getOwner().lock() )
  {
    ActorPtr actor = _ai->getOwner().lock();
    WearerPtr wearer = actor->getFeature<Wearer>();
    if ( wearer )
    {
      ActorPtr weaponActor = wearer->equipped( ItemSlotType::MainHand );
      ActorPtr amunitionActor = wearer->equipped( ItemSlotType::Amunition );
      if ( weaponActor && amunitionActor )
      {
        PickablePtr weapon = weaponActor->getFeature<Pickable>();
        PickablePtr amunition = amunitionActor->getFeature<Pickable>();

        canEnter =  weapon    &&
                    amunition &&
                    amunition->getAmount() > 0 &&
                    amunition->getItemType().amunition == weapon->getItemType().amunition;
      }
    }
  }
  return canEnter;
}


}}
