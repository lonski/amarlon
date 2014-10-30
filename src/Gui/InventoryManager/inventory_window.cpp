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
  _panels[INVENTORY] = MenuPtr( new ItemsMenu(windowWidth / 2, windowHeight) );
  _panels[BODYSLOTS] = MenuPtr( new Menu(windowWidth / 2, windowHeight) );
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
  ItemsMenuPtr invMenu = std::dynamic_pointer_cast<ItemsMenu>( _panels[INVENTORY] );
  assert( invMenu );
  std::vector<Actor*> items = Actor::Player->afContainer()->content();
  _bagItems = invMenu->fillWithItems<LabelMenuItem>( items );

}
//~~~

// === BODY SLOTS SETUP === //

void InventoryWindow::setupBodyPanelWidgets()
{
  _panels[BODYSLOTS]->setTitle("Equipped items");

  fillBodySlots();

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
//~~~

void InventoryWindow::render()
{  
  for (auto pIter = _panels.begin(); pIter != _panels.end(); ++pIter)
  {
    pIter->second->render(*_engine->getConsole());
  }
}

void InventoryWindow::show()
{
  setupBagPanelWidgets();
  setupBodyPanelWidgets();

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

    default:;
  }

  if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER)
  {
    MenuItemPtr menuItem = getSelectedItem();
    int id = std::stol( menuItem->getTag("id") );

    if ( _activePanel == INVENTORY )
    {
      Actor* selected = _bagItems[ id ];
      Pickable* pickable = selected->afPickable();

      Menu itemMenu(40, 1);
      itemMenu.setTitle( selected->getName() );
      itemMenu.centerPosition();

      if ( pickable->getItemSlot() != ItemSlotType::Null )
      {
        LabelMenuItemPtr itemEquip( new LabelMenuItem );
        itemEquip->setValue("Equip");
        itemEquip->setTag("id", "1");
        itemMenu.addItem( itemEquip );
      }

      LabelMenuItemPtr itemDrop( new LabelMenuItem );
      itemDrop->setValue("Drop");
      itemDrop->setTag("id", "2");
      itemMenu.addItem( itemDrop );

      itemMenu.selectNext();
      int id = itemMenu.choose(*_engine->getConsole());

      if ( id == 1 ) //equip
      {
        ItemSlotType slot = pickable->getItemSlot();
        Wearer* wearer = Actor::Player->afWearer();
        Container* container = Actor::Player->afContainer();
        if ( wearer->hasSlot( slot ) ) //check if have valid slot
        {
          bool canEquip = false;
          if ( wearer->isEquipped(slot) ) //unequip existing item
          {
            Actor* unequipped = wearer->unequip(slot);
            if ( unequipped )
            {
              if ( !container->add(unequipped) )
              {
                msgError("You have no free space in inventory,\nto put "+unequipped->getName()+"!");
                wearer->equip( unequipped );
                assert( wearer->isEquipped(slot) );
              }else canEquip = true;
            }else msgError("Cannot unequip " + wearer->equipped(slot)->getName() + "!");
          }else canEquip = true;

          if ( canEquip )
          {

            SlotMenuItemPtr slotItem = std::dynamic_pointer_cast<SlotMenuItem>( _panels[BODYSLOTS]->find((int)slot) );
            assert( slotItem );
            slotItem->setValue("");

            if ( container->remove( selected ) )
            {
              if ( wearer->equip( selected ) )
              {
                slotItem->setValue( selected->getName() );
              }else msgError( "Cannot equip item!" );
            }else msgError( "Cannot remove "+selected->getName()+" from inventory." );
          }

          render();
          fillBag();
          fillBodySlots();

        }else msgError( "You haven't got appropriate slot to equip this item." );
      }
      else if ( id == 2 ) //drop
      {
        menuItem->deselect();
        render();

        bool removed = false;
        if ( pickable->isStackable() && pickable->getAmount() > 1 )
        {
          AmountWindow aWin( pickable->getAmount() );
          int amount = aWin.getAmount();

          if ( amount > 0)
          {
            if ( amount < pickable->getAmount() )
            {
              selected = pickable->spilt(amount);
              removed = (selected != nullptr);
            }
            else
            {
              removed = Actor::Player->afContainer()->remove( selected );
            }
          }
        }
        else
        {
          removed = Actor::Player->afContainer()->remove( selected );
        }

        if ( removed )
        {
          selected->setX( Actor::Player->getX() );
          selected->setY( Actor::Player->getY() );
          _engine->currentMap()->addActor( selected );
          fillBag();
        }else msgError( "Cannot remove "+selected->getName()+" from inventory." );
      }

    }
    else if ( _activePanel == BODYSLOTS )
    {
      SlotMenuItemPtr slotItem = std::dynamic_pointer_cast<SlotMenuItem>( menuItem );
      ItemSlotType slot = static_cast<ItemSlotType>(id);
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
            fillBag();
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

              fillBag();
              fillBodySlots();

            }else msgError( "Cannot remove item from inventory!" );
          }

        }

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

}}
