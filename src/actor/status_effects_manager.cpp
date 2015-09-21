#include "status_effects_manager.h"
#include <algorithm>
#include <effect.h>

namespace amarlon {

StatusEffectsManager::StatusEffectsManager()
{

}

void StatusEffectsManager::add(EffectPtr effect)
{
  if ( effect->getTime() != 0 )
  {
    if ( effect->getTime() == -1 )
      _permEffects.push_back(effect);
    else
      _tempEffects.push_back(effect);
  }
}

void StatusEffectsManager::remove(EffectPtr effect)
{
  auto& container = effect->getTime() == -1 ? _permEffects : _tempEffects;
  auto it = std::find(container.begin(), container.end(),effect);
  if ( it != container.end() )
    container.erase( it );
}

void StatusEffectsManager::tick(int time)
{
  auto it = _tempEffects.begin();
  while ( it != _tempEffects.end())
  {
    EffectPtr& e = *it;
    bool erase = false;

    if ( e->getTime() != -1 ) //omit permament effects
    {
      e->setTime( e->getTime() - time );
      erase = e->getTime() <= 0;
    }

    erase ? _tempEffects.erase(it++) : ++it;
  }
}

std::vector<EffectPtr> StatusEffectsManager::getPermamentEffects() const
{
  return { _permEffects.begin(), _permEffects.end() };
}

std::vector<EffectPtr> StatusEffectsManager::getTemporaryEffects() const
{
  return { _tempEffects.begin(), _tempEffects.end() };
}

StatusEffectsManagerPtr StatusEffectsManager::clone()
{
  StatusEffectsManagerPtr mgr(new StatusEffectsManager);

  for ( auto e : _permEffects )
  {
    mgr->_permEffects.push_back( e->clone() );
  }

  for ( auto e : _tempEffects )
  {
    mgr->_tempEffects.push_back( e->clone() );
  }

  return mgr;
}

}

