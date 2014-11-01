#include "pick_up_window.h"
#include <Gui/Widget/menu/items_menu.h>
#include <Gui/Widget/menu/label_menu_item.h>
#include <Gui/message_box.h>
#include <Actor/ActorFeatures/Container.h>
#include <Gui/AmountWindow.h>
#include <Utils/ItemPicker.h>

namespace amarlon { namespace gui {

PickUpWindow::PickUpWindow(Actor& picker, Container& container,
                           std::function<bool (Actor *)> filterFunc)
  : _picker(picker)
  , _container(container)
  , _filterFunc(filterFunc)
{
}

void PickUpWindow::show()
{
  gui::ItemsMenu menu;
  menu.setTitle("Choose items to pick up");
  menu.centerPosition(false);
  menu.setShowCategories(false);

  std::map<int, Actor*> mappedItems = menu.fillWithItems<gui::LabelMenuItem>( _container.content(&_filterFunc) );

  TCODConsole::root->saveApf("tmp"); //a workaround for "refreshing" console, hanve to access for engine here ;s

  int choosen(-1);
  do
  {
    TCODConsole::root->loadApf("tmp");
    choosen = menu.choose( *TCODConsole::root );

    auto found = mappedItems.find( choosen );
    if ( found != mappedItems.end() )
    {
      Actor* toPick = found->second;
      int itemAmount = toPick->afPickable()->getAmount();
      std::string itemName = toPick->getName();

      if ( int pickedAmount = ItemPicker(&_picker, toPick).pick() )
      {
        if ( itemAmount == pickedAmount )
        {
          if ( _container.remove( toPick ) )
          {
            mappedItems.erase( found );
            menu.removeItem( choosen );
            menu.selectNext();
          }
          else
          {
            msgError( toPick->getName() + " cannot be removed from container!" );
          }
        }
        else
        {
          gui::LabelMenuItemPtr mItem = std::dynamic_pointer_cast<gui::LabelMenuItem>( menu.getSelectedItem() );
          int left = itemAmount - pickedAmount;
          if ( left > 1 ) itemName += " (" + std::to_string(left) + ")";
          mItem->setValue( itemName );
        }

      }
      else
      {
        gui::msgError("Cannot pick up "+toPick->getName()+":\nnot enough space in inventory.");
      }
    }
  }
  while ( choosen != -1 && !mappedItems.empty() );

}


}}
