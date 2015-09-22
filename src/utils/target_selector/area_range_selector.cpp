#include "area_range_selector.h"
#include <engine.h>
#include <actor.h>
#include <gui.h>
#include <console_utils.h>
#include <map.h>

namespace amarlon
{

AreaRangeSelector::AreaRangeSelector(const std::string &selectionMessage)
  : TargetSelector(selectionMessage)
{
  initialize();
}

void AreaRangeSelector::initialize()
{
  tStart.x = Engine::instance().getPlayer()->getX();
  tStart.y = Engine::instance().getPlayer()->getY();
  tEnd = tStart;
}

void AreaRangeSelector::render()
{
  Engine::instance().render();
  Engine::instance().getGui().setStatusMessage( _selectionMessage );
  highlightCell(tEnd.x, tEnd.y);
  highlightFilledCircle( getRadius(), tEnd);
  renderPath(tStart, tEnd);
  TCODConsole::root->flush();
}

Target AreaRangeSelector::select(std::function<bool (ActorPtr)> filterFun)
{
  initialize();

  MapPtr map = Engine::instance().getPlayer()->getMap();
  if ( map )
  {
    TCOD_key_t key;
    while ( key.vk != TCODK_ESCAPE )
    {
      render();
      TCODSystem::waitForEvent(TCOD_KEY_PRESSED, &key, NULL, true);

      int dx(0), dy(0);
      handleDirectionKey(key, dx, dy);

      float distance = calculateDistance(tStart.x, tStart.y, tEnd.x+dx, tEnd.y+dy );
      bool inFov = map->isInFov( tEnd.x+dx, tEnd.y+dy);

      if ( distance <= getRange() && inFov )
      {
        tEnd.x += dx;
        tEnd.y += dy;
        if ( _updateFunction != nullptr) _updateFunction();
      }

      if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER )
      {
        std::function<bool(ActorPtr)> filter = [&](ActorPtr a){ return map->isInFov(a->getX(), a->getY()) && filterFun(a); };
        return Target( map->getActors(tEnd.x, tEnd.y, getRadius(), filter), tEnd.x, tEnd.y );
      }

    }
  }

  return Target();
}

}

