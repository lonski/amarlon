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
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_MOUSE|TCOD_EVENT_KEY_PRESS, &key, &mouse);
    editor.handleInput(mouse, key);
    fflush(stdout);
  }

  return 0;
}

