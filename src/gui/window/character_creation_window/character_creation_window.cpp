#include "character_creation_window.h"
#include <engine.h>
#include <asub_panel.h>

namespace amarlon { namespace gui {

CharacterCreationWindow::CharacterCreationWindow()
{
}

CharacterCreationWindow::~CharacterCreationWindow()
{
}

void CharacterCreationWindow::managePanel(int panel)
{

}

bool CharacterCreationWindow::exitWindow(TCOD_key_t key)
{
  return key.vk == TCODK_ESCAPE;
}

}}
