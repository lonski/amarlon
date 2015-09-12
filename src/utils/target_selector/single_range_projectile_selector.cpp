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
  _tx = 0;
  _ty = 0;
  _x = Engine::instance().getPlayer()->getX();
  _y = Engine::instance().getPlayer()->getY();
  _map = Engine::instance().getPlayer()->getMap();
}

Target SingleRangeProjectileSelector::select(std::function<bool (ActorPtr)> filterFun)
{
  initialize();

  auto actors = _map->getActors([&](ActorPtr a){ return a->getDistance(_x, _y) <= getRange() &&
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

      _tx = (*aIter)->getX();
      _ty = (*aIter)->getY();

      if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER )
      {
        return Target( {*aIter}, _tx, _ty );
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
  renderPath( Target(_x, _y), Target(_tx, _ty) );
  highlightCircle( getRange(), Target({player}, player->getX(), player->getY()), TCODColor::lighterYellow * 0.1);
  Engine::instance().getGui().setStatusMessage( _selectionMessage );

  TCODConsole::root->flush();
}

}
