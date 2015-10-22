#include "character_creation_window.h"
#include <engine.h>
#include <asub_panel.h>
#include <race_selection_panel.h>

namespace amarlon { namespace gui {

CharacterCreationWindow::CharacterCreationWindow()
  : _raceSelection( new RaceSelectionPanel )
{
  setHeight( Engine::screenHeight );
  setWidth( Engine::screenWidth );

  _raceSelection->setPosition(0,0);

}

CharacterCreationWindow::~CharacterCreationWindow()
{
}

AWindow &CharacterCreationWindow::show()
{
  removeAllWidgets();
  _activePanel = CURRENT_STEP;

  _raceSelection->update();
  _raceSelection->selectNext();
  _panels[CURRENT_STEP] = _raceSelection;
  addWidget( _raceSelection );

  AMultiPanelWIndow::show();

  return *this;
}

void CharacterCreationWindow::managePanel(int panel)
{
  _panels[panel]->manage();
}

bool CharacterCreationWindow::exitWindow(TCOD_key_t key)
{
  return key.vk == TCODK_ESCAPE;
}

}}
