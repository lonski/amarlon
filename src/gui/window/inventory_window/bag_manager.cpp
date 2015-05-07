#include "bag_manager.h"
#include <Actor/Actor.h>
#include <gui/widget/menu/label_menu_item.h>
#include <gui/widget/menu/slot_menu_item.h>
#include <gui/message_box.h>
#include <gui/window/amount_window.h>
#include <engine.h>
#include <world/map.h>
#include <utils/messenger.h>

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

  std::vector<Actor*> items = Actor::Player->getFeature<Container>()->content();
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
  itemMenu->setPosition(gui::AWidget::WINDOW_CENTER);
  itemMenu->setTitle( selected->getName() );

  if ( selected->getFeature<Pickable>()->isEquippable() )
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
      msgBox( "Cannot equip item!", gui::MsgType::Error );
    }
  }
  else
  {
    msgBox( "Cannot remove "+item->getName()+" from inventory.", gui::MsgType::Error );
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
