#include "bag_manager.h"
#include <Actor/Actor.h>
#include <Gui/Widget/menu/label_menu_item.h>
#include <Gui/Widget/menu/slot_menu_item.h>
#include <Gui/message_box.h>
#include <Gui/Window/amount_window.h>
#include <Engine.h>
#include <World/Map.h>

namespace amarlon { namespace gui {

BagManager::BagManager(ItemsMenuPtr bagMenu, MenuPtr bodyMenu)
  : _bagMenu(bagMenu)
  , _bodyMenu(bodyMenu)
{
  fillBag();
}

void BagManager::fillBag()
{
  _bagMenu->clear();
  _bagItems.clear();

  std::vector<Actor*> items = Actor::Player->afContainer()->content();
  _bagItems = _bagMenu->fillWithItems<LabelMenuItem>( items );
}

void BagManager::render()
{
  _bagMenu->render( *TCODConsole::root );
  _bodyMenu->render( *TCODConsole::root );
}

// === OPERATION CHOOSING === //
void BagManager::manage()
{
  MenuItemPtr menuItem = _bagMenu->getSelectedItem();
  Actor* selectedItem = _bagItems[ std::stol( menuItem->getTag("id") ) ];

  if ( selectedItem )
  {
    menuItem->deselect(); //needed to repaint black background
    render();

    ItemOperation operation = chooseItemOperationFromMenu(selectedItem);

    switch(operation)
    {
      case EQUIP: equip( selectedItem ); break;
      case DROP: drop( selectedItem ); break;
    }

    fillBag();
    render();
  }
}

BagManager::ItemOperation BagManager::chooseItemOperationFromMenu(Actor* selected)
{
  MenuPtr itemMenu( new Menu(40, 1) );
  itemMenu->centerPosition();
  itemMenu->setTitle( selected->getName() );

  if ( selected->afPickable()->isEquippable() )
  {
    LabelMenuItemPtr itemEquip( new LabelMenuItem );
    itemEquip->setValue("Equip");
    itemEquip->setTag("id", std::to_string(EQUIP));
    itemMenu->addItem( itemEquip );
  }

  LabelMenuItemPtr itemDrop( new LabelMenuItem );
  itemDrop->setValue("Drop");
  itemDrop->setTag("id", std::to_string(DROP));
  itemMenu->addItem( itemDrop );

  itemMenu->selectNext();

  return static_cast<ItemOperation>(itemMenu->choose(*TCODConsole::root));;
}
// ~~~ OPERATION CHOOSING ~~~ //

// === EQUIP === //
void BagManager::equip(Actor* item)
{
  ItemSlotType itemSlot = item->afPickable()->getItemSlot();
  Wearer* playerWearer = Actor::Player->afWearer();

  if ( playerWearer->hasSlot( itemSlot ) )
  {
    if ( canEquip(itemSlot) ) doTheEquip(item);
  }
  else
  {
    msgError( "You haven't got appropriate slot to equip this item." );
  }

}

bool BagManager::canEquip(ItemSlotType slot)
{
  Wearer* playerWearer = Actor::Player->afWearer();
  Container* playerContainer = Actor::Player->afContainer();

  bool slotIsFree = !playerWearer->isEquipped(slot);

  if ( !slotIsFree )
  {
    if ( Actor* unequipped = playerWearer->unequip(slot) ) //try to free it
    {
      slotIsFree = playerContainer->add(unequipped);
      if ( !slotIsFree )
      {
        msgError("You have no free space in inventory for "+unequipped->getName()+"!");
        playerWearer->equip( unequipped );
        assert( playerWearer->isEquipped(slot) );
      }
    }
    else msgError("Cannot unequip " + playerWearer->equipped(slot)->getName() + "!");
  }

  return slotIsFree;
}

void BagManager::doTheEquip(Actor* item)
{
  ItemSlotType slot = item->afPickable()->getItemSlot();
  Wearer* wearer = Actor::Player->afWearer();
  Container* container = Actor::Player->afContainer();

  SlotMenuItemPtr slotItem = std::dynamic_pointer_cast<SlotMenuItem>( _bodyMenu->find((int)slot) );
  assert( slotItem );
  slotItem->setValue("");

  if ( container->remove( item ) )
  {
    if ( wearer->equip( item ) )
    {
      slotItem->setValue( item->getName() );
    }
    else
    {
      msgError( "Cannot equip item!" );
    }
  }
  else
  {
    msgError( "Cannot remove "+item->getName()+" from inventory." );
  }

}
// ~~~ EQUIP ~~~ //

// === DROP === //
void BagManager::drop(Actor* item)
{
  bool stackableHandlingNeeded = item->afPickable()->isStackable() &&
                                 item->afPickable()->getAmount() > 1;

  bool removed = ( stackableHandlingNeeded ? handleStackableDrop(item)
                                           : Actor::Player->afContainer()->remove( item ) );

  if ( removed )
  {
    item->setX( Actor::Player->getX() );
    item->setY( Actor::Player->getY() );
    Engine::instance().currentMap().addActor( item );
  }
  else
  {
    msgError( "Cannot remove "+item->getName()+" from inventory." );
  }
}

bool BagManager::handleStackableDrop(Actor*& item)
{
  bool removed = false;

  int maxAmount = item->afPickable()->getAmount();
  int amount = Engine::instance().windowManager()
                                 .getWindow<gui::AmountWindow>()
                                 .setMaxAmount(maxAmount)
                                 .show()
                                 .downcast<gui::AmountWindow>()
                                 .getAmount();

  if ( amount > 0 && amount < maxAmount )
  {
    item = item->afPickable()->spilt(amount);
    removed = (item != nullptr);
  }
  else if ( amount == maxAmount )
  {
    removed = Actor::Player->afContainer()->remove( item );
  }

  return removed;
}

// ~~~ DROP ~~~ //

}}
