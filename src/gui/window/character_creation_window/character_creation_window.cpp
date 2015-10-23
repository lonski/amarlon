#include "character_creation_window.h"
#include <engine.h>
#include <asub_panel.h>
#include <race_selection_panel.h>
#include <class_selection_panel.h>

namespace amarlon { namespace gui {

CharacterCreationWindow::CharacterCreationWindow()
  : _enterGame(false)
  , _raceSelection( new RaceSelectionPanel )
  , _classSelection( new ClassSelectionPanel )
{
  setHeight( Engine::screenHeight );
  setWidth( Engine::screenWidth );

  _raceSelection->setPosition(0,0);
  _panels[RACE_SELECTION] = _raceSelection;

  _classSelection->setPosition(0,0);
  _panels[CLASS_SELECTION] = _classSelection;
}

CharacterCreationWindow::~CharacterCreationWindow()
{
}

void CharacterCreationWindow::showActivePanel()
{
  removeAllWidgets();
  _panels [ _activePanel ]->update();
  _panels [ _activePanel ]->selectNext();
  addWidget( _panels [ _activePanel ] );
}

AWindow &CharacterCreationWindow::show()
{
  showActivePanel();

  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);

    if ( _enterGame )
    {
      Engine::instance().enterGame();
      break;
    }
  }

  return *this;
}

AWindow &CharacterCreationWindow::setDefaults()
{
  _activePanel = RACE_SELECTION;
  _enterGame = false;

  return *this;
}

void CharacterCreationWindow::handleKey(TCOD_key_t key)
{
  switch ( key.vk )
  {
    case TCODK_DOWN:
    case TCODK_KP2:
    {
      _panels[_activePanel]->selectNext();
      break;
    }
    case TCODK_UP:
    case TCODK_KP8:
    {
      _panels[_activePanel]->selectPrevious();
      break;
    }
    case TCODK_ENTER:
    case TCODK_KPENTER:
    {
      nextStep();
      break;
    }
    default:;
  }
}

void CharacterCreationWindow::nextStep()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  _enterGame = ++cPanel == _panels.end();

  if ( !_enterGame ) _activePanel = cPanel->first;

  showActivePanel();
}

}}
