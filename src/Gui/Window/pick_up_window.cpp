#include "pick_up_window.h"
#include <Gui/Widget/menu/label_menu_item.h>
#include <Gui/message_box.h>
#include <Actor/ActorFeatures/Container.h>
#include <Gui/Window/amount_window.h>
#include <utils/item_picker.h>

namespace amarlon { namespace gui {

PickUpWindow::PickUpWindow()
  : _freezer(TCODConsole::root)
{
  setDefaults();
}

Window &PickUpWindow::setDefaults()
{
  _menu.setTitle("Choose items to pick up");
  _menu.centerPosition(false);
  _menu.setShowCategories(false);

  _picker = nullptr;
  _container = nullptr;
  _filterFunc = [](Actor*){return true;};

  return *this;
}

PickUpWindow& PickUpWindow::setPicker(Actor *picker)
{
  _picker = picker;
  return *this;
}

PickUpWindow& PickUpWindow::setContainer(Container *container)
{
  _container = container;
  return *this;
}

PickUpWindow& PickUpWindow::setFilterFunction(std::function<bool(Actor*)> fun)
{
  _filterFunc = fun;
  return *this;
}

Window& PickUpWindow::show()
{
  if ( _picker && _container)
  {
    _freezer.freeze();

    std::map<int, Actor*> mappedItems = _menu.fillWithItems<gui::LabelMenuItem>( _container->content(&_filterFunc) );
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
        int pickedAmount = ItemPicker(_picker, toPick).pick();

        if ( pickedAmount > 0 )
        {
          _container->remove( toPick );

          mappedItems = _menu.fillWithItems<gui::LabelMenuItem>( _container->content(&_filterFunc) );
          _menu.selectFirst();
        }
      }
    }
    while ( choosen != -1 && !mappedItems.empty() );
  }

  return *this;
}

}}
