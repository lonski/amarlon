#include "single_range_selector.h"
#include <cmath>
#include <engine.h>
#include <map.h>
#include <gui.h>
#include <utils.h>
#include <actor.h>
#include <console_utils.h>


namespace amarlon {

SingleRangeSelector::SingleRangeSelector(const std::string &selectionMessage)
    : TargetSelector(selectionMessage)
{
    initialize();
}

void SingleRangeSelector::initialize()
{
  tStart.x = Engine::instance().getPlayer()->getX();
  tStart.y = Engine::instance().getPlayer()->getY();
  tEnd = tStart;
}

Target SingleRangeSelector::select(std::function<bool (amarlon::ActorPtr)> filterFun)
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
          return Target( map->getActors(tEnd.x, tEnd.y, filterFun), tEnd.x, tEnd.y );
        }

      }
    }

    return Target();
}

void SingleRangeSelector::render()
{
    Engine::instance().render();
    Engine::instance().getGui().setStatusMessage( _selectionMessage );
    highlightCell(tEnd.x, tEnd.y);
    Engine::instance().flush();
}

}

