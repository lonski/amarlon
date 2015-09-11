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
#include <drop_action.h>
#include <equip_action.h>
#include <unequip_action.h>
#include <fixed_size_text_window.h>

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
  InventoryPtr inventory = Actor::Player->getFeature<Inventory>();
  if ( inventory )
  {
    std::function<std::string(ActorPtr)> category_function = [&](ActorPtr a)
                                       {
                                         PickablePtr p = a->getFeature<Pickable>();
                                         return p ? PickableCategory2Str( p->getCategory() ) : "";
                                       };

    _bagMenu->fill<Actor>( inventory->items(), getItemNameAndAmount, category_function);
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
        case DROP: Actor::Player->performAction( std::make_shared<DropAction>(selectedItem, getAmountToDrop(selectedItem) ) ); break;
        //TODO display actor info text instead of test string
        case INSPECT:
          Engine::instance()
              .windowManager()
              .getWindow<FixedSizeTextWindow>()
              .setText( selectedItem->getDescription() )
              .show();
          break;
        default:;
      }

      fillBag();
    }
  }
}

void BagManager::equip(ActorPtr item)
{
  EquipActionPtr equipAction = std::make_shared<EquipAction>(item);
  Actor::Player->performAction( equipAction );

  switch( equipAction->getResult() )
  {
    case EquipResult::AlreadyEquiped:
      { //try to unequip, and then equip again
        if ( Actor::Player->performAction( std::make_shared<UnEquipAction>( item->getFeature<Pickable>()->getItemSlot() )))
        {
          equip( item );
        }
        else
        {
          msgBox( "Cannot unequip currently equipped item!", gui::MsgType::Error );
        }
      }
      break;

    case EquipResult::NoProperSlot:
      msgBox( "You haven't got appropriate slot to equip this item.", gui::MsgType::Error);
      break;

    case EquipResult::Nok:
      msgBox( "Cannot equip item!", gui::MsgType::Error );
      break;

    default:;
  }
}

int BagManager::getAmountToDrop(ActorPtr toDrop)
{
  int amount = 1;

  PickablePtr pickable = toDrop->getFeature<Pickable>();
  if ( pickable && pickable->isStackable() )
  {
    amount = Engine::instance().windowManager()
                               .getWindow<gui::AmountWindow>()
                               .setMaxAmount( pickable->getAmount() )
                               .show()
                               .downcast<gui::AmountWindow>()
                               .getAmount();
  }

  return amount;
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

  ALabelMenuItemPtr itemInfo( new ALabelMenuItem );
  itemInfo->setValue("Inspect");
  itemInfo->setProperty<int>("operation", INSPECT);

  menu.addMenuItem( itemInfo );

  menu.show();
  AMenuItemPtr sItem = menu.getSelectedItem();

  return sItem ? static_cast<ItemOperation>(sItem->getProperty<int>("operation"))
               : INVALID;
}

}}
