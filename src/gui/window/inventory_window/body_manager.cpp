#include "body_manager.h"
#include "actor/actor.h"
#include <amenu_item.h>
#include <aslot_menu_item.h>
#include <alabel_menu_item.h>
#include <gui/message_box.h>
#include <gui/widget/menu/items_menu.h>

namespace amarlon { namespace gui {

BodyManager::BodyManager(MenuPtr bodyMenu)
  : _bodyMenu(bodyMenu)
{
}

void BodyManager::fillBodySlots()
{
  int currentIndex = _bodyMenu->getCurrentIndex();
  _bodyMenu->clear();

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

      ASlotMenuItemPtr newSlot( new ASlotMenuItem( _bodyMenu->getWidth() - 4 ) );
      newSlot->setName( slotName );
      newSlot->setValue( slotValue );
      newSlot->setTag( "id", std::to_string(i) );

      _bodyMenu->addItem( newSlot );
    }
  }

  if ( currentIndex > -1 ) _bodyMenu->select(currentIndex);

}

void BodyManager::manage()
{
  ItemSlotType slot = (ItemSlotType)std::stol( _bodyMenu->getSelectedItem()->getTag("id") );

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
    ItemsMenu equipMenu;
    equipMenu.setTitle("Choose item to equip");
    equipMenu.setShowCategories(false);
    equipMenu.setPosition(gui::AWidget::WINDOW_CENTER);

    std::map<int, Actor*> mappedItems = equipMenu.fillWithItems<ALabelMenuItem>( equipableItems );

    equipMenu.selectNext(); //activate first menu option

    auto found = mappedItems.find( equipMenu.choose( *TCODConsole::root ) );

    if ( found != mappedItems.end() ) equipItem(found->second);
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
