#include "body_manager.h"
#include "actor/actor.h"
#include <amenu_item.h>
#include <aslot_menu_item.h>
#include <alabel_menu_item.h>
#include <gui/message_box.h>
#include <menu_window.h>

namespace amarlon { namespace gui {

BodyManager::BodyManager(int w, int h)
  : AInventoryPanel(w, h)
  , _bodyMenu( new AMenu )
{
  setTitle("Equipped items");

  _bodyMenu->setPosition(2,2);
  addWidget(_bodyMenu);
}

void BodyManager::fillBodySlots()
{  
  int selectedSlot = -1;
  if ( AMenuItemPtr selected = _bodyMenu->getSelectedItem() )
  {
    selectedSlot = selected->getProperty<int>("ItemSlotType");
  }

  _bodyMenu->removeAllItems();

  Wearer* wearer = Actor::Player->getFeature<Wearer>();
  assert(wearer);

  for( int i = (int)ItemSlotType::Null + 1; i != (int)ItemSlotType::End; ++i)
  {
    ItemSlotType slot = static_cast<ItemSlotType>(i);
    if ( wearer->hasSlot(slot) )
    {
      Actor* eq = wearer->equipped(slot);

      std::string slotValue = eq ? eq->getName() : "";
      std::string slotName = ItemSlotType2Str(i);

      ASlotMenuItemPtr newSlot( new ASlotMenuItem( getWidth() - 4 ) );
      newSlot->setName( slotName );
      newSlot->setValue( slotValue );
      newSlot->setProperty<int>( "ItemSlotType", i );

      _bodyMenu->addItem( newSlot );

      if ( i == selectedSlot ) _bodyMenu->select(newSlot);
    }
  }
}

void BodyManager::manage()
{  
  if ( AMenuItemPtr item = _bodyMenu->getSelectedItem() )
  {
    ItemSlotType slot = static_cast<ItemSlotType>( item->getProperty<int>("ItemSlotType") );

    if ( Actor::Player->getFeature<Wearer>()->isEquipped( slot ) )
    {
      unequipItem(slot);
    }
    else
    {
      chooseAndEquipItem(slot);
    }

    fillBodySlots();
  }
}

// === UNEQUIP === //
void BodyManager::unequipItem(ItemSlotType slot)
{
  Wearer* playerWearer = Actor::Player->getFeature<Wearer>();
  Container* playerContainer = Actor::Player->getFeature<Container>();

  if ( Actor* item = playerWearer->unequip( slot ) )
  {
    clearSelectedItemSlotValue();

    if ( !playerContainer->add(item) )
    {
      msgBox("Item cannot be unequipped:\nNot enough space in inventory",
             gui::MsgType::Error);
      playerWearer->equip(item);
    }
  }
  else
  {
    msgBox("Item cannot be unequipped!", gui::MsgType::Error);
  }
}

void BodyManager::clearSelectedItemSlotValue()
{
  AMenuItemPtr menuItem = _bodyMenu->getSelectedItem();
  ASlotMenuItemPtr slotMenuItem = std::dynamic_pointer_cast<ASlotMenuItem>( menuItem );

  slotMenuItem->setValue("");
}
// ~~~ UNEQUIP ~~~ //

// === EQUIP === //
void BodyManager::chooseAndEquipItem(ItemSlotType slot)
{
  std::vector<Actor*> equipableItems = getEquipableItemsList(slot);

  if ( !equipableItems.empty() )
  {
    gui::MenuWindow& window = Engine::instance().windowManager().getWindow<gui::MenuWindow>();

    window.setTitle("Choose item to equip");
    window.setPosition(gui::AWidget::WINDOW_CENTER);
    window.fill<Actor>( equipableItems, [](Actor* a){ return a->getName(); } );
    window.show();

    if ( AMenuItemPtr mItem = window.getSelectedItem() )
    {
      equipItem(mItem->getObject<Actor>());
    }
  }
  else
  {
    msgBox("You don't have any item, that fit this slot.", gui::MsgType::Error);
  }

}

void BodyManager::equipItem(Actor* toEquip)
{
  if (Actor::Player->getFeature<Container>()->remove( toEquip ))
  {
    if ( !Actor::Player->getFeature<Wearer>()->equip( toEquip ) )
    {
      msgBox( "Cannot equip item!", gui::MsgType::Error );
      Actor::Player->getFeature<Container>()->add( toEquip );
    }
  }
  else
  {
    msgBox( "Cannot remove item from inventory!", gui::MsgType::Error );
  }
}

AMenuItemPtr BodyManager::getSelectedItem()
{
  return _bodyMenu->getSelectedItem();
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

bool BodyManager::setSlotValue(ItemSlotType slot, const std::string& value)
{
  bool foundSlotAndSetName = false;

  auto itemIter = std::find_if(_bodyMenu->begin(), _bodyMenu->end(),
                               [&slot](const AMenuItemPtr& item)
                               {
                                  return item->getProperty<int>("ItemSlotType") == static_cast<int>(slot);
                               });

  if ( itemIter != _bodyMenu->end() )
  {
    (*itemIter)->setValue(value);
    foundSlotAndSetName = true;
  }

  return foundSlotAndSetName;
}

std::vector<Actor *> BodyManager::getEquipableItemsList(ItemSlotType slot)
{
  std::function<bool(Actor*)> filterFun = [&](Actor* a)-> bool
  {
    return a->hasFeature<Pickable>() && a->getFeature<Pickable>()->getItemSlot() == slot;
  };

  return Actor::Player->getFeature<Container>()->content( &filterFun );
}
// ~~~ EQUIP ~~~ //

}}
