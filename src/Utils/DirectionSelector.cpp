#include "DirectionSelector.h"
#include <libtcod.hpp>
#include "Utils.h"

DirectionSelector::DirectionSelector()
{
}

void DirectionSelector::select(int &dx, int &dy)
{
  TCOD_key_t lastKey;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,NULL, true);

  handleDirectionKey(lastKey, dx, dy);
}
