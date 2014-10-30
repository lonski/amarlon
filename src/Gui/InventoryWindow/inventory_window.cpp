#include "inventory_window.h"
#include <iostream>
#include <algorithm>
#include <Utils/glodef.h>
#include <Actor/Actor.h>
#include <Actor/ActorFeatures/Wearer/item_slot_type.h>
#include <Gui/Widget/label.h>
#include <Gui/Widget/list.h>
#include <Gui/Widget/menu/label_menu_item.h>
#include <Gui/Widget/menu/slot_menu_item.h>
#include <Gui/message_box.h>
#include <Gui/Widget/menu/items_menu.h>
#include <Engine.h>
#include <World/Map.h>
#include <Gui/AmountWindow.h>

namespace amarlon { namespace gui {

InventoryWindow::InventoryWindow(Engine *engine)
  : windowHeight( gloScreenHeight )
  , windowWidth( gloScreenWidth )  
  , _activePanel(INVENTORY)
  , _engine(engine)
{
  ItemsMenuPtr invMenu( new ItemsMenu(windowWidth / 2, windowHeight) );
  invMenu->setPosition(windowWidth / 2, 0);
  invMenu->setTitle("Inventory");

  MenuPtr bodyMenu( new Menu(windowWidth / 2, windowHeight) );
  bodyMenu->setTitle("Equipped items");

  _panels[INVENTORY] = invMenu;
  _panels[BODYSLOTS] = bodyMenu;

  _invMgr.reset( new InventoryManager( invMenu, bodyMenu, _engine ) );
}

void InventoryWindow::render()
{
  for (auto pIter = _panels.begin(); pIter != _panels.end(); ++pIter)
  {
    pIter->second->render(*_engine->getConsole());
  }
}

void InventoryWindow::fillBodySlots()
{
  _panels[BODYSLOTS]->clear();
  Wearer* wearer = Actor::Player->afWearer();
  assert(wearer);

  for( int i = (int)ItemSlotType::Null + 1; i != (int)ItemSlotType::End; ++i)
  {
    ItemSlotType slot = static_cast<ItemSlotType>(i);
    if ( wearer->hasSlot(slot) )
    {
      Actor* eq = wearer->equipped(slot);

      std::string slotValue = eq ? eq->getName() : "";
      std::string slotName = ItemSlotType2Str(i);

      SlotMenuItemPtr newSlot( new SlotMenuItem( _panels[BODYSLOTS]->getWidth() - 4 ) );
      newSlot->setSlotName( slotName );
      newSlot->setValue( slotValue );
      newSlot->setTag( "id", std::to_string(i) );

      _panels[BODYSLOTS]->addItem( newSlot );
    }
  }

}

void InventoryWindow::show()
{
  fillBodySlots();
  _invMgr->fillBag();

  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    render();
    _engine->getConsole()->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);

    if ( (key.vk == TCODK_CHAR && key.c == 'i') || (key.vk == TCODK_ESCAPE) )
      break;
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
      if ( getSelectedItem() )
      {
        switch( _activePanel)
        {
          case INVENTORY: _invMgr->manage(); break;
          case BODYSLOTS: manageBodySlots(); break;
        }
      }
      break;
    }
    default:;
  }

}

void InventoryWindow::manageBodySlots()
{
  MenuItemPtr menuItem = getSelectedItem();
  int menuItemId = std::stol( menuItem->getTag("id") );

  SlotMenuItemPtr slotItem = std::dynamic_pointer_cast<SlotMenuItem>( menuItem );
  ItemSlotType slot = static_cast<ItemSlotType>(menuItemId);
  Wearer* wearer = Actor::Player->afWearer();
  Actor* selected = wearer->equipped( slot );

  if ( selected ) //if item is equipped, then unequip
  {
    slotItem->setValue("");
    selected = wearer->unequip( slot );
    if ( selected )
    {
      if (Actor::Player->afContainer()->add( selected ) )
      {
        _invMgr->fillBag();
      } else
      {
        msgError("Item cannot be unequipped:\nNot enough space in inventory");
        //equip back
        wearer->equip( selected );
        fillBodySlots();
      }
    } else msgError("Item cannot be unequipped!");
  }
  else //show window with equippable items
  {
    std::function<bool(Actor*)> filterFun = [&](Actor* a)-> bool
    {
      return a->afPickable() && a->afPickable()->getItemSlot() == slot;
    };

    std::vector<Actor*> equipableItems = Actor::Player->afContainer()->content( &filterFun );

    if ( equipableItems.empty() )
    {
      msgError("You don't have any item, that fit this slot.");
    }
    else
    {
      ItemsMenu equipMenu;
      equipMenu.setTitle("Choose item to equip");
      equipMenu.setShowCategories(false);
      equipMenu.centerPosition();

      std::map<int, Actor*> mappedItems = equipMenu.fillWithItems<LabelMenuItem>( equipableItems );
      equipMenu.selectNext();
      int choosed = equipMenu.choose(*_engine->getConsole());

      auto found = mappedItems.find(choosed);
      if ( found != mappedItems.end() )
      {
        Actor* toEquip = found->second;
        if (Actor::Player->afContainer()->remove( toEquip ))
        {
          if ( !wearer->equip( toEquip ) )
          {
            msgError( "Cannot equip item!" );
            Actor::Player->afContainer()->add( toEquip );
          }

          _invMgr->fillBag();
          fillBodySlots();

        }else msgError( "Cannot remove item from inventory!" );
      }

    }

  }
}

MenuItemPtr InventoryWindow::getSelectedItem()
{
  MenuItemPtr sItem;
  int index = _panels[_activePanel]->getCurrentIndex();
  if ( index > -1 )
  {
    sItem = _panels[_activePanel]->getSelectedItem();
  }

  return sItem;
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
