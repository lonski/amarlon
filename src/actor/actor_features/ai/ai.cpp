#include "ai.h"
#include <iostream>
#include <actor_descriptions.h>
#include <monster_ai.h>
#include <player_ai.h>
#include <actor_action.h>
#include <actor.h>
#include <status_effects_manager.h>

namespace amarlon {

const ActorFeature::Type Ai::featureType = ActorFeature::AI;

Ai::Ai()
{
}

Ai::Ai(DescriptionPtr /*dsc*/)
{
}

AiPtr Ai::create(DescriptionPtr dsc)
{
  AiPtr ai;

  AiDescriptionPtr aDsc = std::dynamic_pointer_cast<AiDescription>(dsc);
  if ( aDsc )
  {
    switch (aDsc->type)
    {
      case AiType::MonsterAi: ai.reset( new MonsterAi(aDsc) ); break;
      case AiType::PlayerAi:  ai.reset( new PlayerAi(aDsc) ); break;
      default :;
    }
  }

  return ai;
}

bool Ai::performAction(ActorActionPtr action)
{
  return action && canOperate() ? action->perform( getOwner().lock() ) : false;
}

bool Ai::isSleeping() const
{
  bool r = false;

  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    r = owner->getStatusEffects().hasEffect( "Sleep" );
  }

  return r;
}

void Ai::wakeUp()
{
  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    owner->getStatusEffects().remove( "Sleep" );
  }
}

bool Ai::canOperate() const
{
  return !isSleeping();
}

void Ai::cloneBase(AiPtr /*ai*/)
{

}

}

