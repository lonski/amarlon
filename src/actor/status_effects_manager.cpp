#include "status_effects_manager.h"
#include <algorithm>
#include <actor.h>
#include <status_effect.h>

namespace amarlon {

StatusEffectsManager::StatusEffectsManager(ActorPtr owner)
  : _owner(owner)
{
}

void StatusEffectsManager::add(StatusEffectPtr effect)
{
  if ( effect->getDuration() != 0 )
  {
    _effects.push_back(effect);
    notifyAdd(effect);
  }
}

void StatusEffectsManager::remove(StatusEffectPtr effect)
{
  auto it = std::find(_effects.begin(), _effects.end(),effect);
  if ( it != _effects.end() )
  {
    notifyRemove(effect);
    _effects.erase( it );
  }
}

void StatusEffectsManager::tick(int time)
{
  auto it = _effects.begin();
  while ( it != _effects.end())
  {
    auto& e = *it;
    bool erase = false;

    if ( e->getDuration() != -1 ) //omit permament effects
    {
      e->setDuration( e->getDuration() - time );
      erase = e->getDuration() <= 0;
    }

    if ( erase )
    {
      notifyRemove(e);
      if ( _owner.lock() && e->cancel(_owner.lock()) )
        _effects.erase(it++);
      else
        printf("LOG: failed to cancel effect SpellId=%s",e->getName().c_str());
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

