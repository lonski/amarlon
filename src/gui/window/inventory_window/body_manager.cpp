#include "body_manager.h"
#include "actor/actor.h"
#include <amenu_item.h>
#include <aslot_menu_item.h>
#include <alabel_menu_item.h>
#include <gui/message_box.h>
#include <menu_window.h>

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
  if ( AMenuItemPtr item = _bodyMenu->getSelectedItem() )
  {
    ItemSlotType slot = static_cast<ItemSlotType>( item->getProperty<int>("ItemSlotType") );

    if ( Actor::Player->getFeature<Wearer>()->isEquipped( slot ) )
    {
      if ( unequipItem(slot) )
      {
        item->setValue("");
      }
    }
    else
    {
      ActorPtr toEquip = chooseItemToEquip(slot);
      if ( equipItem(toEquip) )
      {
        item->setValue( toEquip->getName() );
      }
    }
  }
}

void BodyManager::fillBodySlots()
{  
  _bodyMenu->removeAllItems();

  WearerPtr wearer = Actor::Player->getFeature<Wearer>();
  assert(wearer);

  for( int i = (int)ItemSlotType::Null + 1; i != (int)ItemSlotType::End; ++i)
  {
    ItemSlotType slot = static_cast<ItemSlotType>(i);
    if ( wearer->hasSlot(slot) )
    {
      ActorPtr eItem = wearer->equipped(slot);

      ASlotMenuItemPtr slotMenuItem( new ASlotMenuItem( getWidth() - 2*MARGIN ) );
      slotMenuItem->setProperty<int>( "ItemSlotType", i );
      slotMenuItem->setName( ItemSlotType2Str(i) );
      slotMenuItem->setValue( eItem ? eItem->getName() : "" );

      _bodyMenu->addItem( slotMenuItem );
    }
  }
}

bool BodyManager::unequipItem(ItemSlotType slot)
{
  bool success = false;

  WearerPtr playerWearer = Actor::Player->getFeature<Wearer>();
  ContainerPtr playerContainer = Actor::Player->getFeature<Container>();

  if ( ActorPtr item = playerWearer->unequip( slot ) )
  {
    if ( playerContainer->add(item) )
    {
      success = true;
    }
    else
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

  return success;
}

ActorPtr BodyManager::chooseItemToEquip(ItemSlotType slot)
{
  ActorPtr toEquip;
  std::vector<ActorPtr> equipableItems = getEquipableItemsList(slot);

  if ( !equipableItems.empty() )
  {
    gui::MenuWindow& window = Engine::instance().windowManager().getWindow<gui::MenuWindow>();

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

  return Actor::Player->getFeature<Container>()->content( &filterFun );
}

bool BodyManager::equipItem(ActorPtr toEquip)
{
  bool success = false;

  if (Actor::Player->getFeature<Container>()->remove( toEquip ))
  {
    if ( Actor::Player->getFeature<Wearer>()->equip( toEquip ) )
    {
      success = true;
    }
    else
    {
      msgBox( "Cannot equip item!", gui::MsgType::Error );
      Actor::Player->getFeature<Container>()->add( toEquip );
    }
  }
  else
  {
    msgBox( "Cannot remove item from inventory!", gui::MsgType::Error );
  }

  return success;
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
