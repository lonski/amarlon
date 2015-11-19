#include "ai.h"
#include <iostream>
#include <actor_descriptions.h>
#include <actor_action.h>
#include <actor.h>
#include <status_effects_manager.h>
#include <move_action.h>
#include <use_skill_action.h>
#include <fsm.h>
#include <map.h>
#include <fsm_state.h>
#include <lua_state.h>
#include <engine.h>

namespace amarlon {

const ActorFeature::Type Ai::featureType = ActorFeature::AI;

Ai::Ai()
  : Ai(nullptr)
{
}

Ai::Ai(DescriptionPtr /*dsc*/)
  : _fsm( new FSM(this) )
  , _scriptId(0)
  , _trackCount(0)
  , _type(AiType::Null)
{
}

AiType Ai::getAiType() const
{
  return _type;
}

AiPtr Ai::create(DescriptionPtr dsc)
{
  AiPtr ai;

  AiDescriptionPtr aDsc = std::dynamic_pointer_cast<AiDescription>(dsc);
  if ( aDsc )
  {
    ai.reset( new Ai );
    ai->_scriptId = aDsc->script;
    ai->_type = aDsc->type;

    if ( ai->getAiType() == AiType::PlayerAi )
    {
      ai->changeState( FSMStateType::PLAYER_CONTROLLED );
    }
    else
    {
      ai->changeState( FSMStateType::IDLE );
    }
  }

  return ai;
}

bool Ai::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  AiPtr crhs = std::dynamic_pointer_cast<Ai>(rhs);

  if (crhs)
  {
    equal = _scriptId == crhs->_scriptId;
    equal &= _type == crhs->_type;
  }

  return equal;
}

ActorFeaturePtr Ai::clone()
{
  AiPtr cloned( new Ai );
  cloned->_trackCount = _trackCount;
  cloned->_flags = _flags;
  cloned->_scriptId = _scriptId;
  cloned->_currentTarget = _currentTarget;
  cloned->_type = _type;
  cloned->changeState( getCurrentState() );

  return cloned;
}

int Ai::update()
{
  int turns = 0;
  if ( canOperate() )
  {
    executeScript();
    if ( _fsm ) turns = _fsm->update();
  }

  return turns;
}

void Ai::executeScript()
{
  if ( getAiType() == AiType::GenericAi && _scriptId == 0) _scriptId = 1;

  if ( _scriptId > 0 )
  {
    lua_api::LuaState& lua = Engine::instance().getLuaState();
    if ( lua.execute( getScript() ) )
    {
      try
      {
        luabind::call_function<void>(
            lua()
          , "onUpdate"
          , getOwner().lock()
        );
      }
      catch(luabind::error& e)
      {
        lua.logError(e);
      }
    }
  }
}

bool amarlon::Ai::changeState(amarlon::FSMStateType type)
{
  return _fsm && _fsm->changeState( type );
}

FSMStateType Ai::getCurrentState() const
{
  return _fsm->getCurrentState()->getType();
}

bool Ai::performAction(ActorActionPtr action)
{
  bool r = false;

  if ( action )
  {
    updateHidingStatus( action );
    updateSneakingStatus( action );
    r = action->perform( getOwner().lock() );
  }

  return r;
}

void Ai::updateSneakingStatus(ActorActionPtr action)
{
  ActorPtr owner = getOwner().lock();
  if ( isSneaking() && owner )
  {
    bool remainSneaking = false;

    if ( std::dynamic_pointer_cast<MoveAction>(action) )
    {
      if ( CharacterPtr c = owner->getFeature<Character>() )
      {
        remainSneaking = UseSkillAction( c->getSkill(SkillId::SilentMove), Target(owner)).perform( owner );
      }
    }

    if ( !remainSneaking ) setSneaking(false);
  }
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

bool Ai::isSneaking() const
{
  return _flags[2];
}

void Ai::setSneaking(bool sneaking)
{
  _flags.set(2, sneaking);
  getOwner().lock()->setVisible( !sneaking );
}

bool Ai::canOperate() const
{
  return !isSleeping();
}

std::string Ai::getScript() const
{
  return "scripts/ai/" + std::to_string( static_cast<int>(_scriptId) ) + ".lua";
}

void Ai::setTarget(Target target)
{
  _currentTarget = target;
}

void Ai::setTarget(ActorPtr actor)
{
  _currentTarget = Target(actor);
}

Target Ai::getTarget() const
{
  return _currentTarget;
}

bool Ai::hasTarget() const
{
  return getTarget() != Target();
}

ActorVector Ai::getEnemiesInFov() const
{
  ActorVector enemies;

  ActorPtr owner = getOwner().lock();
  MapPtr map = owner ? owner->getMap() : nullptr;
  if ( owner && map && owner->isInFov() )
  {
    enemies = map->getActors([&](ActorPtr a){ return a->isAlive() &&
                                                     a->isInFov() &&
                                                     a->isHostileTo(owner); });
  }

  return enemies;
}

int Ai::getTrackingTurns() const
{
  return _trackCount;
}

void Ai::setTrackingTurns(int turns)
{
  _trackCount = turns;
}

bool Ai::isHunting() const
{
  return _trackCount > 0 && getOwner().lock()->isAlive();
}

}

