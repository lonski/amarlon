#include "amultipanel_window.h"
#include <engine.h>
#include <asub_panel.h>

namespace amarlon { namespace gui {


AMultiPanelWindow::AMultiPanelWindow()
  : _activePanel(0)
{
}

AMultiPanelWindow::~AMultiPanelWindow()
{
}

AWindow& AMultiPanelWindow::show()
{
  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    loopUpdate();
    render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);

    if ( exitWindow(key) ) break;
  }

  return *this;
}

void AMultiPanelWindow::handleKey(TCOD_key_t key)
{
  switch ( key.vk )
  {
    case TCODK_TAB:
    {
      activateNextPanel();
      break;
    }
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
    case TCODK_LEFT:
    case TCODK_KP4:
    {
      do
      {
        activatePreviousPanel();
      }
      while ( !_panels[ _activePanel ]->isActivable() );
      break;
    }
    case TCODK_RIGHT:
    case TCODK_KP6:
    {
      do
      {
        activateNextPanel();
      }
      while ( !_panels[ _activePanel ]->isActivable() );
      break;
    }
    case TCODK_ENTER:
    case TCODK_KPENTER:
    {
      managePanel(_activePanel);
      break;
    }
    default:;
  }
}

void AMultiPanelWindow::activateNextPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( ++cPanel == _panels.end() ) cPanel = _panels.begin();

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

void AMultiPanelWindow::activatePreviousPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( cPanel != _panels.begin()  )
    --cPanel;
  else
    std::advance(cPanel, _panels.size() - 1 );

  _activePanel = cPanel->first;
  cPanel->second->activate();
}


}}
