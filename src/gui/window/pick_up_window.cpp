#include "pick_up_window.h"
#include <gui/widget/menu/label_menu_item.h>
#include <gui/message_box.h>
#include <Actor/ActorFeatures/Container.h>
#include <gui/window/amount_window.h>
#include <utils/item_picker.h>
#include <utils/amarlon_except.h>

namespace amarlon { namespace gui {

PickUpWindow::PickUpWindow()
{
  setDefaults();
}

Window &PickUpWindow::setDefaults()
{
  _menu.setTitle("Choose items to pick up");
  _menu.setPosition(gui::AWidget::GAME_SCREEN_CENTER);
  _menu.setShowCategories(false);

  _picker = nullptr;
  _container = nullptr;
  _filterFunc = [](Actor*){return true;};

  _afterPickUpAction = [](const std::string&, int){};
  _inventoryFullAction = [](const std::string&){ gui::msgBox("Inventory is full!", gui::MsgType::Error); };

  return *this;
}

Window& PickUpWindow::show()
{
  if ( _picker && _container)
  {
    std::map<int, Actor*> mappedItems = _menu.fillWithItems<gui::LabelMenuItem>( _container->content(&_filterFunc) );
    _menu.selectFirst();

    int choosen(-1);
    do
    {
      Engine::instance().render();
      choosen = _menu.choose( *TCODConsole::root );

      auto found = mappedItems.find( choosen );
      if ( found != mappedItems.end() )
      {
        Actor* toPick = found->second;
        std::string itemName = toPick->getName();

        try
        {
          int pickedAmount = ItemPicker(_picker, toPick, _container).pick();

          mappedItems = _menu.fillWithItems<gui::LabelMenuItem>( _container->content(&_filterFunc) );
          _menu.selectFirst();

          _afterPickUpAction(itemName, pickedAmount);
        }
        catch( inventory_full& e )
        {
          _inventoryFullAction(e.getItemName());
        }
      }
    }
    while ( choosen != -1 && !mappedItems.empty() );
  }

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

PickUpWindow& PickUpWindow::setAfterPickupAction(std::function<void (const std::string &, int)> fun)
{
  _afterPickUpAction = fun;
  return *this;
}

PickUpWindow &PickUpWindow::setInventoryFullAction(std::function<void (const std::string &)> fun)
{
  _inventoryFullAction = fun;
  return *this;
}

PickUpWindow &PickUpWindow::setWindowTitle(const std::string &title)
{
  _menu.setTitle(title);
  return *this;
}

}}
