#include "inventory_window.h"
#include <iostream>
#include <algorithm>
#include <actor.h>
#include <item_slot_type.h>
#include <alabel_menu_item.h>
#include <aslot_menu_item.h>
#include <gui/message_box.h>
#include <gui/widget/menu/items_menu.h>
#include <engine.h>
#include <world/map.h>
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
  _bodyMgr.reset( new BodyManager(windowWidth / 2, windowHeight) );
  _bagMgr.reset( new BagManager( *_bodyMgr, windowWidth / 2, windowHeight ) );
  _bagMgr->setPosition(windowWidth / 2, 0);

  _panels[BODYSLOTS] = _bodyMgr;
  _panels[INVENTORY] = _bagMgr;
}

AWindow &InventoryWindow::setDefaults()
{
  return *this;
}

AWindow& InventoryWindow::show()
{
  _bodyMgr->fillBodySlots();
  _bagMgr->fillBag();

  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    render();
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);

    if ( (key.vk == TCODK_CHAR && key.c == 'i') || (key.vk == TCODK_ESCAPE) )
      break;
  }

  return *this;
}

void InventoryWindow::render()
{
  for (auto pIter = _panels.begin(); pIter != _panels.end(); ++pIter)
  {
    pIter->second->render(*TCODConsole::root);
  }
}

void InventoryWindow::handleKey(TCOD_key_t key)
{
  render();

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
      activatePreviousPanel();
      break;
    }
    case TCODK_RIGHT:
    case TCODK_KP6:
    {
      activateNextPanel();
      break;
    }
    case TCODK_ENTER:
    case TCODK_KPENTER:
    {
      switch( _activePanel)
      {
        case INVENTORY: _bagMgr->manage(); break;
        case BODYSLOTS: _bodyMgr->manage(); _bagMgr->fillBag(); break;
      }
      break;
    }
    default:;
  }

  render();
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
