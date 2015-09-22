#include "body_manager.h"
#include "actor/actor.h"
#include <amenu_item.h>
#include <aslot_menu_item.h>
#include <alabel_menu_item.h>
#include <gui/message_box.h>
#include <menu_window.h>
#include <unequip_action.h>
#include <equip_action.h>

const unsigned MARGIN = 2;

namespace amarlon { namespace gui {

BodyManager::BodyManager(int w, int h)
  : AInventoryPanel(w, h)
  , _bodyMenu( new AMenu )
{
  setTitle("Equipped items");

  _bodyMenu->setPosition(MARGIN,MARGIN);
  addWidget(_bodyMenu);
}

void BodyManager::manage()
{
  AMenuItemPtr item = _bodyMenu->getSelectedItem();
  if ( item )
  {
    ItemSlotType slot = static_cast<ItemSlotType>( item->getProperty<int>("ItemSlotType") );

    if ( Engine::instance().getPlayer()->getFeature<Wearer>()->isEquipped( slot ) )
    {
      if ( unequipItem(slot) )
      {
        item->setValue("");
      }
    }
    else
    {
      ActorPtr toEquip = chooseItemToEquip(slot);
      if ( toEquip && equipItem(toEquip) )
      {
        item->setValue( toEquip->getName() );
      }
    }
  }
}

void BodyManager::fillBodySlots()
{  
  _bodyMenu->removeAllItems();

  WearerPtr wearer = Engine::instance().getPlayer()->getFeature<Wearer>();
  if ( wearer )
  {
    for (auto slot : ItemSlotType())
    {
      if ( wearer->hasSlot(slot) )
      {
        ActorPtr eItem = wearer->equipped(slot);

        ASlotMenuItemPtr slotMenuItem( new ASlotMenuItem( getWidth() - 2*MARGIN ) );
        slotMenuItem->setProperty<int>( "ItemSlotType", static_cast<int>(slot) );
        slotMenuItem->setName( ItemSlotType2Str(slot) );
        slotMenuItem->setValue( eItem ? eItem->getName() : "" );

        _bodyMenu->addItem( slotMenuItem );
      }
    }
  }
}

bool BodyManager::unequipItem(ItemSlotType slot)
{
  UnEquipActionPtr action = std::make_shared<UnEquipAction>(slot);
  Engine::instance().getPlayer()->performAction( action );

  UnEquipResult status = action->getResult();
  switch ( status )
  {
    case UnEquipResult::InventoryFull:
      msgBox("Item cannot be unequipped:\nNot enough space in inventory", gui::MsgType::Error);
      break;

    case UnEquipResult::Nok:
      msgBox("Item cannot be unequipped!", gui::MsgType::Error);
      break;
    default:;
  }

  return status == UnEquipResult::Ok;
}

ActorPtr BodyManager::chooseItemToEquip(ItemSlotType slot)
{
  ActorPtr toEquip;
  std::vector<ActorPtr> equipableItems = getEquipableItemsList(slot);

  if ( !equipableItems.empty() )
  {
    gui::MenuWindow& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();

    window.setTitle("Choose item to equip");
    window.setPosition(gui::AWidget::WINDOW_CENTER);
    window.fill<Actor>( equipableItems, [](ActorPtr a){ return a->getName(); } );
    window.show();

    if ( AMenuItemPtr mItem = window.getSelectedItem() )
    {
      toEquip = mItem->getObject<Actor>();
    }
  }
  else
  {
    msgBox("You don't have any item, that fit this slot.", gui::MsgType::Error);
  }

  return toEquip;
}

std::vector<ActorPtr > BodyManager::getEquipableItemsList(ItemSlotType slot)
{
  std::function<bool(ActorPtr)> filterFun = [&](ActorPtr a)-> bool
  {
    return a->hasFeature<Pickable>() && a->getFeature<Pickable>()->getItemSlot() == slot;
  };

  return Engine::instance().getPlayer()->getFeature<Inventory>()->items( filterFun );
}

bool BodyManager::equipItem(ActorPtr toEquip)
{
  EquipActionPtr action = std::make_shared<EquipAction>(toEquip);
  Engine::instance().getPlayer()->performAction( action );
  EquipResult result = action->getResult();

  switch(result)
  {
    case EquipResult::Nok:
      msgBox( "Cannot equip item!", gui::MsgType::Error );
      break;
    case EquipResult::AlreadyEquiped:
      msgBox( "Another item is already equipped on this slot!", gui::MsgType::Error );
      break;
    case EquipResult::NoProperSlot:
      msgBox( "There is no proper slot to equip this item!", gui::MsgType::Error );
      break;
    default:;
  }

  return result == EquipResult::Ok;
}

void BodyManager::selectNext()
{
  _bodyMenu->selectNext();
}

void BodyManager::selectPrevious()
{
  _bodyMenu->selectPrevious();
}

void BodyManager::activate()
{
  AInventoryPanel::activate();
  _bodyMenu->selectNext();
}

void BodyManager::deactivate()
{
  AInventoryPanel::deactivate();
  _bodyMenu->deselect();
}

}}

