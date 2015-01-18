#include "inventory_window.h"
#include <iostream>
#include <algorithm>
#include "actor/actor.h"
#include "actor/actor_features/wearer/item_slot_type.h"
#include "gui/widget/label.h"
#include "gui/widget/list.h"
#include "gui/widget/menu/label_menu_item.h"
#include "gui/widget/menu/slot_menu_item.h"
#include "gui/message_box.h"
#include "gui/widget/menu/items_menu.h"
#include "gui/window/amount_window.h"
#include "engine.h"
#include "world/map.h"

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
  ItemsMenuPtr bagMenu( new ItemsMenu(windowWidth / 2, windowHeight) );
  bagMenu->setPosition(windowWidth / 2, 0);
  bagMenu->setTitle("Inventory");

  MenuPtr bodyMenu( new Menu(windowWidth / 2, windowHeight) );
  bodyMenu->setTitle("Equipped items");

  _panels[INVENTORY] = bagMenu;
  _panels[BODYSLOTS] = bodyMenu;

  _bagMgr.reset( new BagManager( bagMenu, bodyMenu ) );
  _bodyMgr.reset( new BodyManager( bodyMenu ) );
}

Window &InventoryWindow::setDefaults()
{
  return *this;
}

Window& InventoryWindow::show()
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
      if ( _panels[_activePanel]->getSelectedItem() )
      {
        switch( _activePanel)
        {
          case INVENTORY: _bagMgr->manage(); break;
          case BODYSLOTS: _bodyMgr->manage(); _bagMgr->fillBag(); break;
        }
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
