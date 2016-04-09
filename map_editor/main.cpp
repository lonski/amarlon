#include <libtcod.hpp>
#include "map_editor.h"

int main()
{
  amarlon::map_editor::MapEditor editor;
  editor.init();

  while ( !TCODConsole::isWindowClosed() && !editor.isQuitting() )
  {
    editor.render();
    TCODConsole::root->flush();

    TCOD_mouse_t mouse;
    TCODSystem::waitForEvent(TCOD_EVENT_MOUSE, NULL, &mouse, true);
    editor.handleInput(mouse);
  }

  return 0;
}

