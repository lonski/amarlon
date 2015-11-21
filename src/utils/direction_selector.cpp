#include "direction_selector.h"
#include "utils/utils.h"
#include <engine.h>
#include <gui.h>

namespace amarlon {

DirectionSelector::DirectionSelector(const std::string &selectionMessage)
  : _selectionMessage(selectionMessage)
{
}

bool DirectionSelector::select(int &dx, int &dy)
{
  Engine::instance().getGui().setStatusMessage( _selectionMessage );
  Engine::instance().flush();

  TCOD_key_t lastKey;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,NULL, true);

  return handleDirectionKey(lastKey, dx, dy);
}

}

