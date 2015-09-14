#include "single_range_projectile_selector.h"
#include <engine.h>
#include <map.h>
#include <actor.h>
#include <gui.h>
#include <console_utils.h>
#include <messenger.h>

namespace amarlon {

SingleRangeProjectileSelector::SingleRangeProjectileSelector(const std::string &selectionMessage)
  : TargetSelector(selectionMessage)
{
  initialize();
}

void SingleRangeProjectileSelector::initialize()
{
  tStart.x = Engine::instance().getPlayer()->getX();
  tStart.y = Engine::instance().getPlayer()->getY();
  tEnd = tStart;
  _map = Engine::instance().getPlayer()->getMap();
}

Target SingleRangeProjectileSelector::select(std::function<bool (ActorPtr)> filterFun)
{
  initialize();

  auto actors = _map->getActors([&](ActorPtr a){ return a->getDistance(tStart.x, tStart.y) <= getRange() &&
                                                        a->isAlive() &&
                                                        _map->isInFov(a->getX(), a->getY() ) &&
                                                        a->getId() != ActorType::Player &&
                                                        filterFun(a); });
  auto aIter = actors.begin();

  TCOD_key_t key;
  while ( key.vk != TCODK_ESCAPE )
  {
    if ( aIter != actors.end() )
    {
      if ( key.vk == TCODK_TAB )
      {
        ++aIter;
        if ( aIter == actors.end() ) aIter = actors.begin();
      }

      tEnd.x = (*aIter)->getX();
      tEnd.y = (*aIter)->getY();

      if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER )
      {
        return Target( {*aIter}, tEnd.x, tEnd.y );
      }
    }

    render();
    TCODSystem::waitForEvent(TCOD_KEY_PRESSED, &key, NULL, true);
  }

  return Target();
}

void SingleRangeProjectileSelector::render()
{
  ActorPtr player = Engine::instance().getPlayer();

  Engine::instance().render();
  renderPath( tStart, tEnd );
  highlightFilledCircle( getRange(), Target({player}, player->getX(), player->getY()));
  Engine::instance().getGui().setStatusMessage( _selectionMessage );

  TCODConsole::root->flush();
}

}
