#include "pick_up_window.h"
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
  , _freezer(TCODConsole::root)
{
  _menu.setTitle("Choose items to pick up");
  _menu.centerPosition(false);
  _menu.setShowCategories(false);
}

void PickUpWindow::show()
{
  _freezer.freeze();

  std::map<int, Actor*> mappedItems = _menu.fillWithItems<gui::LabelMenuItem>( _container.content(&_filterFunc) );
  _menu.selectFirst();

  int choosen(-1);
  do
  {
    _freezer.restore();
    choosen = _menu.choose( *TCODConsole::root );

    auto found = mappedItems.find( choosen );
    if ( found != mappedItems.end() )
    {
      Actor* toPick = found->second;
      int pickedAmount = ItemPicker(&_picker, toPick).pick();

      if ( pickedAmount > 0 )
      {        
        _container.remove( toPick );

        mappedItems = _menu.fillWithItems<gui::LabelMenuItem>( _container.content(&_filterFunc) );
        _menu.selectFirst();
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
