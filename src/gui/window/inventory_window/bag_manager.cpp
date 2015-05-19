#include "bag_manager.h"
#include "actor/actor.h"
#include <alabel_menu_item.h>
#include <aslot_menu_item.h>
#include <gui/message_box.h>
#include <gui/window/amount_window.h>
#include <engine.h>
#include <world/map.h>
#include <utils/messenger.h>
#include <menu_window.h>
#include <item_action.h>

namespace amarlon { namespace gui {

BagManager::BagManager(int w, int h)
  : AInventoryPanel(w, h)
  , _bagMenu( new AMenu )
{
  _bagMenu->setPosition(2,2);  
  _bagMenu->setAutosize(false);
  _bagMenu->setWidth( getWidth() - 2 );
  _bagMenu->setHeight( getHeight() - 2 );

  addWidget(_bagMenu);
  setTitle("Inventory");
  fillBag();
}

void BagManager::fillBag()
{
  ContainerPtr inventory = Actor::Player->getFeature<Container>();
  if ( inventory )
  {
    std::function<std::string(ActorPtr)> category_function = [&](ActorPtr a)
                                       {
                                         PickablePtr p = a->getFeature<Pickable>();
                                         return p ? PickableCategory2Str( p->getCategory() ) : "";
                                       };

    _bagMenu->fill<Actor>( inventory->content(), getItemNameAndAmount, category_function);
  }
}

void BagManager::selectNext()
{
  _bagMenu->selectNext();
}

void BagManager::selectPrevious()
{
  _bagMenu->selectPrevious();
}

void BagManager::activate()
{
  AInventoryPanel::activate();
  _bagMenu->selectNext();
}

void BagManager::deactivate()
{
  AInventoryPanel::deactivate();
  _bagMenu->deselect();
}

void BagManager::manage()
{
  if ( AMenuItemPtr mItem = _bagMenu->getSelectedItem() )
  {
    ActorPtr selectedItem( mItem->getObject<Actor>() );
    if ( selectedItem )
    {
      ItemOperation operation = chooseItemOperationFromMenu(selectedItem);

      switch(operation)
      {
        case EQUIP: equip( selectedItem ); break;
        case DROP: ItemAction(Actor::Player, selectedItem, Actor::Player->getFeature<Container>()).drop() ; break;
        default:;
      }

      fillBag();
    }
  }
}

BagManager::ItemOperation BagManager::chooseItemOperationFromMenu(ActorPtr selected)
{
  MenuWindow& menu = Engine::instance().windowManager().getWindow<MenuWindow>();
  menu.setTitle( selected->getName() );
  menu.setPosition( gui::AWidget::WINDOW_CENTER );

  if ( selected->getFeature<Pickable>()->isEquippable() )
  {
    ALabelMenuItemPtr itemEquip( new ALabelMenuItem );
    itemEquip->setValue("Equip");
    itemEquip->setProperty<int>("operation", EQUIP);

    menu.addMenuItem( itemEquip );
  }

  ALabelMenuItemPtr itemDrop( new ALabelMenuItem );
  itemDrop->setValue("Drop");
  itemDrop->setProperty<int>("operation", DROP);

  menu.addMenuItem( itemDrop );

  menu.show();
  AMenuItemPtr sItem = menu.getSelectedItem();

  return sItem ? static_cast<ItemOperation>(sItem->getProperty<int>("operation"))
               : INVALID;
}

void BagManager::equip(ActorPtr item)
{
  ItemSlotType itemSlot = item->getFeature<Pickable>()->getItemSlot();
  WearerPtr playerWearer = Actor::Player->getFeature<Wearer>();

  if ( playerWearer->hasSlot( itemSlot ) )
  {
    if ( canEquip(itemSlot) ) doTheEquip(item);
  }
  else
  {
    msgBox( "You haven't got appropriate slot to equip this item.", gui::MsgType::Error);
  }

}

bool BagManager::canEquip(ItemSlotType slot)
{
  WearerPtr playerWearer = Actor::Player->getFeature<Wearer>();
  ContainerPtr playerContainer = Actor::Player->getFeature<Container>();

  bool slotIsFree = !playerWearer->isEquipped(slot);

  if ( !slotIsFree )
  {
    if ( ActorPtr unequipped = playerWearer->unequip(slot) ) //try to free it
    {
      slotIsFree = playerContainer->add(unequipped);
      if ( !slotIsFree )
      {
        msgBox("You have no free space in inventory for "+unequipped->getName()+"!",
               gui::MsgType::Error);
        playerWearer->equip( unequipped );
        assert( playerWearer->isEquipped(slot) );
      }
    }
    else msgBox("Cannot unequip " + playerWearer->equipped(slot)->getName() + "!",
                gui::MsgType::Error);
  }

  return slotIsFree;
}

void BagManager::doTheEquip(ActorPtr item)
{
  WearerPtr wearer = Actor::Player->getFeature<Wearer>();
  ContainerPtr container = Actor::Player->getFeature<Container>();

  if ( container->remove( item ) )
  {
    if ( !wearer->equip( item ) )
    {
      msgBox( "Cannot equip item!", gui::MsgType::Error );
    }
  }
  else
  {
    msgBox( "Cannot remove "+item->getName()+" from inventory.", gui::MsgType::Error );
  }

}

}}
