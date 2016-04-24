#include "status_effects_manager.h"
#include <algorithm>
#include <actor.h>
#include <status_effect.h>

namespace amarlon {

StatusEffectsManager::StatusEffectsManager(ActorPtr owner)
  : _owner(owner)
{
}

StatusEffectsManager::~StatusEffectsManager()
{
  removeAll();
}

bool StatusEffectsManager::add(StatusEffectPtr effect)
{
  bool r = false;

  if ( effect->getDuration() != 0 )
  {
    auto it = std::find_if(_effects.begin(), _effects.end(), [&](StatusEffectPtr e){return *e == *effect;});
    if ( it != _effects.end() ) //effect already applied
    {
      (*it)->setDuration( std::max((*it)->getDuration(), effect->getDuration()) );
    }
    else
    {
      _effects.push_back(effect);
      r = true;
    }
    notifyAdd(effect);
  }

  return r;
}

void StatusEffectsManager::remove(StatusEffectPtr effect, bool notify)
{
  auto it = std::find(_effects.begin(), _effects.end(),effect);
  if ( it != _effects.end() )
  {
    effect->cancel(_owner.lock());
    if(notify) notifyRemove(effect);
    _effects.erase( it );
  }
}

void StatusEffectsManager::remove(std::function<bool (StatusEffectPtr)> cmp, bool notify)
{
  auto it = std::find_if(_effects.begin(),
                         _effects.end(),
                         cmp);

  if ( it != _effects.end() )
  {
    (*it)->cancel(_owner.lock());
    if(notify) notifyRemove( *it );
    _effects.erase( it );
  }
}

void StatusEffectsManager::remove(const std::string& name, bool notify)
{
  auto it = std::find_if(_effects.begin(),
                         _effects.end(),
                         [&](StatusEffectPtr e){return e->getName() == name;});

  if ( it != _effects.end() )
  {
    (*it)->cancel(_owner.lock());
    if(notify) notifyRemove( *it );
    _effects.erase( it );
  }
}

void StatusEffectsManager::removeAll()
{
  ActorPtr owner = _owner.lock();

  if ( owner )
    for ( auto e : _effects )
      e->cancel(owner);

  _effects.clear();
}

void StatusEffectsManager::tick(int time, GameTimeUnit res)
{
  auto it = _effects.begin();
  while ( it != _effects.end())
  {
    auto& e = *it;
    bool erase = false;

    if ( e->getDuration() != -1 ) //omit permament effects
    {
      e->setDuration( e->getDuration() - time*(int)res );
      erase = e->getDuration() <= 0;
    }

    if ( res == GameTimeUnit::Day && _owner.lock() )
    {
      e->tickDay(_owner.lock());
    }

    if ( erase )
    {
      notifyRemove(e);
      if ( _owner.lock() && e->cancel(_owner.lock()) )
        _effects.erase(it++);
    }
    else
    {
      ++it;
    }
  }
}

std::vector<StatusEffectPtr> StatusEffectsManager::getEffects() const
{
  return { _effects.begin(), _effects.end() };
}

std::vector<ColoredString> StatusEffectsManager::getEffectsStringList() const
{
  std::vector<ColoredString> effects;

  for(auto e : _effects )
  {
    effects.push_back( ColoredString( e->getName(), e->getDuration() != -1 ? TCODColor::lightCyan
                                                                           : TCODColor::darkerCyan ) );
  }

  return effects;
}

bool StatusEffectsManager::hasEffect(const std::string& name) const
{
  for( auto e : _effects )
    if ( e->getName() == name ) return true;

  return false;
}

StatusEffectsManagerPtr StatusEffectsManager::clone()
{
  StatusEffectsManagerPtr mgr(new StatusEffectsManager(*this));

  return mgr;
}

void StatusEffectsManager::notifyAdd(StatusEffectPtr e)
{
  ActorPtr a = _owner.lock();
  if ( a )
  {
    a->notify(Event(EventId::Actor_EffectAdded, {{ "effect", e->getName()} }));
  }
}

void StatusEffectsManager::notifyRemove(StatusEffectPtr e)
{
  ActorPtr a = _owner.lock();
  if ( a )
  {
    a->notify(Event(EventId::Actor_EffectRemoved, {{ "effect", e->getName()}} ));
  }
}

}

