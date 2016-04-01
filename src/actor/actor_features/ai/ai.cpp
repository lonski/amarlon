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

const ActorFeature::Type Ai::FeatureType = ActorFeature::AI;

/* Flag bits */
const int IS_HIDING_BIT = 1;
const int IS_SNEAKING_BIT = 2;

Ai::Ai()
{
  initialize();
}

Ai::Ai(const Ai &rhs)
{
  *this = rhs;
}

Ai::Ai(const AiData &data)
{
  _data.CopyFrom(data);
  initialize();
}

void Ai::initialize()
{
  _trackCount = 0;
  _fsm.reset(new FSM(this));

  if ( getAiType() == AiType::PlayerAi )
  {
    changeState( FSMStateType::PLAYER_CONTROLLED );
  }
  else
  {
    changeState( FSMStateType::IDLE );
  }
}

AiType Ai::getAiType() const
{
  return static_cast<AiType>(_data.type());
}

AiPtr Ai::create(const AiData &data)
{
  return AiPtr( new Ai(data) );
}

bool Ai::operator==(const Ai &rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Ai &Ai::operator=(const Ai &rhs)
{
  if ( this != &rhs )
  {
    _trackCount = rhs._trackCount;
    _currentTarget = rhs._currentTarget;
    _data.CopyFrom(rhs._data);
    changeState(rhs.getCurrentState());
  }
  return *this;
}

const AiData &Ai::getData() const
{
  return _data;
}

const ::google::protobuf::Message& Ai::getDataPolymorphic() const
{
  return getData();
}

int Ai::update()
{
  int turns = 0;

  ActorPtr tgt = getTarget().firstActor();
  if ( tgt && ( !tgt->isVisible() || !tgt->isAlive() ) )
  {
    clearTarget();
  }

  if ( canOperate() )
  {
    executeScript();
    if ( _fsm ) turns = _fsm->update();
  }

  return turns;
}

void Ai::executeScript()
{
  if ( getAiType() == AiType::GenericAi && _data.script() == 0) _data.set_script(1);

  if ( _data.script() > 0 )
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

ActorFeature::Type Ai::getFeatureType()
{
  return Ai::FeatureType;
}

ActorActionResult Ai::performAction(ActorActionPtr action)
{
  ActorActionResult r = ActorActionResult::Nok;

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
        remainSneaking = UseSkillAction( c->getSkill(SkillId::SilentMove), Target(owner))
            .perform( owner ) == ActorActionResult::Ok;
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
        remainHidden = UseSkillAction( c->getSkill(SkillId::Hide), Target(owner))
            .perform( owner ) == ActorActionResult::Ok;
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
  ::google::protobuf::uint32 f = _data.flags();
  return isBitSet(f, IS_HIDING_BIT);
}

void Ai::setHiding(bool hiding)
{
  ::google::protobuf::uint32 f = _data.flags();
  setBit(f, IS_HIDING_BIT, hiding);

  getOwner().lock()->setVisible( !hiding );

  EventId event = hiding ? EventId::Actor_Hidden : EventId::Actor_CancelHidden;
  if ( ActorPtr owner = getOwner().lock() ) owner->notify( Event( event ));
}

bool Ai::isSneaking() const
{
  ::google::protobuf::uint32 f = _data.flags();
  return isBitSet(f, IS_SNEAKING_BIT);
}

void Ai::setSneaking(bool sneaking)
{
  ::google::protobuf::uint32 f = _data.flags();
  setBit(f, IS_SNEAKING_BIT, sneaking);
  getOwner().lock()->setVisible( !sneaking );
}

bool Ai::canOperate() const
{
  return !isSleeping();
}

std::string Ai::getScript() const
{
  return "scripts/ai/" + std::to_string( static_cast<int>(_data.script()) ) + ".lua";
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

void Ai::clearTarget()
{
  setTarget( Target() );
}

ActorVector Ai::getEnemiesInFov() const
{
  ActorVector enemies;

  ActorPtr owner = getOwner().lock();
  MapPtr map = owner ? owner->getMap() : nullptr;
  if ( owner && map && owner->isInFov() )
  {
    enemies = map->getActors([&](ActorPtr a){ return a->isAlive()   &&
                                                     a->isInFov()   &&
                                                     a->isVisible() &&
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

std::string Ai::debug(const std::string &linebreak)
{
  std::string d = " " + linebreak + "-----AI-----"+linebreak;

  d += "Type = " + toStr(_data.type()) + linebreak;
  d += "Script = " + toStr(_data.script()) + linebreak;
  d += "TrackCount = " + toStr(_trackCount) + linebreak;

  d += "Current state = " + toStr((int)getCurrentState()) + linebreak;
  ActorPtr tA = _currentTarget.firstActor();
  if ( tA ) d+= "Target = " + tA->getName() + linebreak;

  d += "----------------" + linebreak;

  return d;
}


}

