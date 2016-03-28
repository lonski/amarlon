#include "actor_wrapper.h"
#include <character.h>
#include <actor.h>
#include <engine.h>
#include <lua_state.h>
#include <monster.h>
#include <status_effect.h>
#include <status_effects_manager.h>

namespace amarlon { namespace lua_api {

ActorWrapper::ActorWrapper(ActorPtr actor)
  : _actor(actor)
{
}

ActorWrapper::~ActorWrapper()
{
}

int ActorWrapper::getLevel()
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      return character->getLevel();
    }
  }
  return 0;
}

int ActorWrapper::getX() const
{
  return _actor ? _actor->getX() : 0;
}

int ActorWrapper::getY() const
{
  return _actor ? _actor->getY() : 0;
}

void ActorWrapper::takeHeal(Damage heal, ActorWrapper healer)
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      character->takeHeal(heal, healer.getActor());
    }
  }
}

void ActorWrapper::takeDamage(Damage dmg, ActorWrapper attacker)
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      character->takeDamage(dmg, attacker.getActor());
    }
  }
}

void ActorWrapper::setAttackModifier(int modifier)
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      character->setTmpAttackModifier(modifier);
    }
  }
}

int ActorWrapper::getAttackModifier() const
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      return character->getTmpAttackModifier();
    }
  }
  return 0;
}

void ActorWrapper::setSavingThrowModifier(int modifier, int savingThrowType)
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      character->setTmpSavingThrowModifier(static_cast<SavingThrows::Type>(savingThrowType), modifier);
    }
  }
}

int ActorWrapper::getSavingThrowModifier(int savingThrowType)
{
  if ( _actor )
  {
    CharacterPtr character = _actor->getFeature<Character>();
    if ( character )
    {
      return character->getTmpSavingThrowModifier(static_cast<SavingThrows::Type>(savingThrowType));
    }
  }
  return 0;
}

void ActorWrapper::setMoraleModifier(int modifier)
{
  if ( _actor )
  {
    MonsterPtr monster = std::dynamic_pointer_cast<Monster>(_actor->getFeature<Character>());
    if ( monster )
    {
      monster->setTmpMoraleModifier(modifier);
    }
  }
}

int ActorWrapper::getMoraleModifier()
{
  if ( _actor )
  {
    MonsterPtr monster = std::dynamic_pointer_cast<Monster>(_actor->getFeature<Character>());
    if ( monster )
    {
      monster->getTmpMoraleModifier();
    }
  }
  return 0;
}

void ActorWrapper::addStatusEffect(StatusEffectPtr effect)
{
  if (_actor)
  {
    _actor->getStatusEffects().add(effect);
  }
}

bool ActorWrapper::isAllyOf(ActorWrapper actor)
{
  return _actor ? _actor->isAllyOf(actor.getActor()) : false;
}

std::string ActorWrapper::getName() const
{
  return _actor ? _actor->getName() : "";
}

ActorPtr ActorWrapper::getActor() const
{
  return _actor;
}

}}

