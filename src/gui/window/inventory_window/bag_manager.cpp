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

namespace amarlon { namespace gui {

BagManager::BagManager(BodyManager& body, int w, int h)
  : AInventoryPanel(w, h)
  , _bagMenu( new ItemsMenu )
  , _body(body)
{
  _bagMenu->setPosition(2,2);
  _bagMenu->setFrame(false);
  addWidget(_bagMenu);
  setTitle("Inventory");
  fillBag();
}

void BagManager::fillBag()
{
  _bagMenu->clear();
  _bagItems.clear();

  std::vector<Actor*> items = Actor::Player->getFeature<Container>()->content();
  _bagItems = _bagMenu->fillWithItems<ALabelMenuItem>( items );
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
  _bagMenu->deactivate();
}

// === OPERATION CHOOSING === //
void BagManager::manage()
{
  AMenuItemPtr menuItem = _bagMenu->getSelectedItem();
  Actor* selectedItem = _bagItems[ menuItem->getProperty<int>("id") ];

  if ( selectedItem )
  {
    ItemOperation operation = chooseItemOperationFromMenu(selectedItem);

    switch(operation)
    {
      case EQUIP: equip( selectedItem ); break;
      case DROP: drop( selectedItem ); break;
      default:;
    }

    fillBag();
  }
}

BagManager::ItemOperation BagManager::chooseItemOperationFromMenu(Actor* selected)
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
// ~~~ OPERATION CHOOSING ~~~ //

// === EQUIP === //
void BagManager::equip(Actor* item)
{
  ItemSlotType itemSlot = item->getFeature<Pickable>()->getItemSlot();
  Wearer* playerWearer = Actor::Player->getFeature<Wearer>();

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
  Wearer* playerWearer = Actor::Player->getFeature<Wearer>();
  Container* playerContainer = Actor::Player->getFeature<Container>();

  bool slotIsFree = !playerWearer->isEquipped(slot);

  if ( !slotIsFree )
  {
    if ( Actor* unequipped = playerWearer->unequip(slot) ) //try to free it
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

void BagManager::doTheEquip(Actor* item)
{  
  ItemSlotType slot = item->getFeature<Pickable>()->getItemSlot();
  Wearer* wearer = Actor::Player->getFeature<Wearer>();
  Container* container = Actor::Player->getFeature<Container>();

  if ( _body.setSlotValue(slot, "" ) )
  {
    if ( container->remove( item ) )
    {
      if ( wearer->equip( item ) )
      {
        _body.setSlotValue(slot, item->getName() );
      }
      else
      {
        msgBox( "Cannot equip item!", gui::MsgType::Error );
      }
    }
    else
    {
      msgBox( "Cannot remove "+item->getName()+" from inventory.", gui::MsgType::Error );
    }
  }
  else
  {
    msgBox( "Proper item slot not available.", gui::MsgType::Error );
  }
}
// ~~~ EQUIP ~~~ //

// === DROP === //
void BagManager::drop(Actor* item)
{
  bool stackableHandlingNeeded = item->getFeature<Pickable>()->isStackable() &&
                                 item->getFeature<Pickable>()->getAmount() > 1;

  bool removed = ( stackableHandlingNeeded ? handleStackableDrop(item)
                                           : Actor::Player->getFeature<Container>()->remove( item ) );

  if ( removed )
  {
    item->setX( Actor::Player->getX() );
    item->setY( Actor::Player->getY() );
    Messenger::message()->actorDropped(Actor::Player, item, item->getFeature<Pickable>()->getAmount());
    Engine::instance().currentMap().addActor( item );
  }
  else
  {
    msgBox( "Cannot remove "+item->getName()+" from inventory.", gui::MsgType::Error );
  }
}

bool BagManager::handleStackableDrop(Actor*& item)
{
  bool removed = false;

  int maxAmount = item->getFeature<Pickable>()->getAmount();
  int amount = Engine::instance().windowManager()
                                 .getWindow<gui::AmountWindow>()
                                 .setMaxAmount(maxAmount)
                                 .show()
                                 .downcast<gui::AmountWindow>()
                                 .getAmount();

  if ( amount > 0 && amount < maxAmount )
  {
    item = item->getFeature<Pickable>()->spilt(amount);
    removed = (item != nullptr);
  }
  else if ( amount == maxAmount )
  {
    removed = Actor::Player->getFeature<Container>()->remove( item );
  }

  return removed;
}

// ~~~ DROP ~~~ //

}}
