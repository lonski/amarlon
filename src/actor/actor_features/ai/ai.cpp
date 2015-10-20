#include "ai.h"
#include <iostream>
#include <actor_descriptions.h>
#include <monster_ai.h>
#include <player_ai.h>
#include <actor_action.h>
#include <actor.h>
#include <status_effects_manager.h>
#include <move_action.h>
#include <use_skill_action.h>

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
  bool r = false;

  if ( action )
  {
    updateHidingStatus( action );
    r = action->perform( getOwner().lock() );
  }

  return r;
}

void Ai::updateHidingStatus(ActorActionPtr action)
{
  ActorPtr owner = getOwner().lock();
  if ( isHiding() && owner )
  {
    bool remainHidden = false;

    if ( std::dynamic_pointer_cast<MoveAction>(action) )
    {
      if ( CharacterPtr c = owner->getFeature<Character>() )
      {
        remainHidden = UseSkillAction( c->getSkill(SkillId::Hide), Target(owner)).perform( owner );
      }
    }

    if ( !remainHidden ) setHiding(false);
  }
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

bool Ai::isHiding() const
{
  return _flags[0];
}

void Ai::setHiding(bool hiding)
{
  _flags.set(0, hiding);
  getOwner().lock()->setVisible( !hiding );

  EventId event = hiding ? EventId::Actor_Hidden : EventId::Actor_CancelHidden;
  if ( ActorPtr owner = getOwner().lock() ) owner->notify( Event( event ));
}

bool Ai::canOperate() const
{
  return !isSleeping();
}

void Ai::cloneBase(AiPtr /*ai*/)
{

}

}

