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

namespace amarlon { namespace gui {

InventoryWindow::InventoryWindow(Actor *actor)
  : windowHeight( gloScreenHeight )
  , windowWidth( gloScreenWidth )  
  , _actor(actor)
  , _activePanel(INVENTORY)
{
  _panels[INVENTORY] = MenuPtr( new Menu(windowWidth / 2, windowHeight) );
  _panels[BODYSLOTS] = MenuPtr( new Menu(windowWidth / 2, windowHeight) );

  setupBagPanelWidgets();
  setupBodyPanelWidgets();

  //_panels[INVENTORY]->activate();
}

// === INVENTORY SETUP === //
void InventoryWindow::setupBagPanelWidgets()
{  
  _panels[INVENTORY]->setPosition(windowWidth / 2, 0);
  _panels[INVENTORY]->setTitle("Inventory");

  fillBag();
}

void InventoryWindow::fillBag()
{
  _panels[INVENTORY]->clear();
  _bagItems.clear();

  std::vector<Actor*> items = _actor->afContainer()->content();
  int id = -1;
  std::for_each(items.begin(), items.end(), [&](Actor* i)
  {
    Pickable* item = i->afPickable();
    assert( item );

    std::string category = PickableCategory2Str( item->getCategory() );
    std::string name = i->getName();

    if ( item->getAmount() > 1 && item->isStackable() )
    {
      name += " (" + std::to_string( item->getAmount() ) + ")";
    }

    LabelMenuItemPtr newItem( new LabelMenuItem );
    newItem->setValue( name );
    newItem->setTag("category", category);
    newItem->setTag("id", std::to_string(++id));
    newItem->setColor(TCODColor::lightChartreuse);

    _panels[INVENTORY]->addItem(newItem);

    _bagItems.insert( std::make_pair(id, i) );
  });

}
//~~~

// === BODY SLOTS SETUP === //
void InventoryWindow::setupBodyPanelWidgets()
{
  _panels[BODYSLOTS]->setTitle("Equipped items");

  Wearer* wearer = _actor->afWearer();

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
      newSlot->setSlotValue( slotValue );
      newSlot->setTag( "id", std::to_string(i) );

      _panels[BODYSLOTS]->addItem( newSlot );
    }
  }

}
//~~~

void InventoryWindow::render(TCODConsole &console)
{
  for (auto pIter = _panels.begin(); pIter != _panels.end(); ++pIter)
  {
    pIter->second->render(console);
  }
}

void InventoryWindow::show(TCODConsole &console)
{
  TCOD_key_t key;

  while( !(key.vk == TCODK_ESCAPE)               &&
         !(key.vk == TCODK_CHAR && key.c == 'i') &&
         !(TCODConsole::isWindowClosed()))
  {      
    render(console);
    console.flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    handleKey(key);
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

    default:;
  }

  //temp for tests
  if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER)
  {
    int index = _panels[INVENTORY]->getCurrentIndex();
    if ( index > -1 )
    {
      MenuItemPtr sItem = _panels[INVENTORY]->getSelectedItem();
      int id = std::stol( sItem->getTag("id") );

      Actor* selected = _bagItems[ id ];
      std::cout << "\n Item selected = " << selected->getName();
      std::cout.flush();
    }
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

}}
