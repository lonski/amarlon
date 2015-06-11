#include "inventory_window.h"
#include <iostream>
#include <algorithm>
#include <actor.h>
#include <item_slot_type.h>
#include <alabel_menu_item.h>
#include <aslot_menu_item.h>
#include <message_box.h>
#include <engine.h>
#include <amount_window.h>
#include <amenu.h>

namespace amarlon { namespace gui {

InventoryWindow::InventoryWindow()
  : windowHeight( Engine::screenHeight )
  , windowWidth( Engine::screenWidth )
  , _activePanel(INVENTORY)
{  
  initalize();
}

void InventoryWindow::initalize()
{
  const int CHAR_INFO_HEIGHT = 16;

  _bodyMgr.reset( new BodyManager(windowWidth / 2, windowHeight) );
  _bagMgr.reset( new BagManager( windowWidth / 2, windowHeight - CHAR_INFO_HEIGHT ) );
  _bagMgr->setPosition(windowWidth / 2, 0);

  _charInfo.reset( new CharacterInfo( windowWidth / 2, CHAR_INFO_HEIGHT ) );
  _charInfo->setPosition(windowWidth / 2, windowHeight - CHAR_INFO_HEIGHT );
  _charInfo->update();

  _panels[BODYSLOTS] = _bodyMgr;
  _panels[INVENTORY] = _bagMgr;
  _panels[CHARACTER_INFO] = _charInfo;

}

AWindow &InventoryWindow::setDefaults()
{
  return *this;
}

void InventoryWindow::render(TCODConsole& console)
{
  for (auto pIter = _panels.begin(); pIter != _panels.end(); ++pIter)
  {
    pIter->second->render(console);
  }
}

AWindow& InventoryWindow::refreshData()
{
  _bodyMgr->fillBodySlots();
  _bagMgr->fillBag();
  _charInfo->update();

  return *this;
}

AWindow& InventoryWindow::show()
{
  refreshData();

  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);

    if ( (key.vk == TCODK_CHAR && key.c == 'i') || (key.vk == TCODK_ESCAPE) )
      break;
  }

  return *this;
}

void InventoryWindow::handleKey(TCOD_key_t key)
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
      switch( _activePanel)
      {
        case INVENTORY: _bagMgr->manage(); _bodyMgr->fillBodySlots(); _charInfo->update(); break;
        case BODYSLOTS: _bodyMgr->manage(); _bagMgr->fillBag(); _charInfo->update(); break;
        default:;
      }
      break;
    }
    default:;
  }

}

void InventoryWindow::activateNextPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( ++cPanel == _panels.end() ) cPanel = _panels.begin();

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

void InventoryWindow::activatePreviousPanel()
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
