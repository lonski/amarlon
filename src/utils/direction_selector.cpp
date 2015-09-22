#include "direction_selector.h"
#include "utils/utils.h"

namespace amarlon {

DirectionSelector::DirectionSelector()
{
}

bool DirectionSelector::select(int &dx, int &dy)
{
  TCOD_key_t lastKey;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,NULL, true);

  return handleDirectionKey(lastKey, dx, dy);
}

}

