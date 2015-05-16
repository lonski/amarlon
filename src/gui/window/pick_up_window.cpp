#include "pick_up_window.h"
#include <alabel_menu_item.h>
#include <message_box.h>
#include <amount_window.h>
#include <container.h>
#include <item_picker.h>
#include <amarlon_except.h>
#include <actor.h>

namespace amarlon { namespace gui {

PickUpWindow::PickUpWindow()
  : _menu( new AMenu )
{
  addWidget(_menu);
  setDefaults();  
}

AWindow &PickUpWindow::setDefaults()
{
  setTitle("Choose items to pick up");
  setPosition(gui::AWidget::GAME_SCREEN_CENTER);
  setFrame(true);
  setHeight(2);
  setWidth(40);

  _picker = nullptr;
  _container = nullptr;
  _filterFunc = [](Actor*){return true;};

  _afterPickUpAction = [](const std::string&, int){};
  _inventoryFullAction = [](const std::string&){ gui::msgBox("Inventory is full!", gui::MsgType::Error); };

  return *this;
}

void PickUpWindow::init()
{
  setWidth ( std::max( _menu->getWidth() + 4, getWidth() ) );
  setHeight( std::max( _menu->getHeight() + 4, getHeight() ) );

  _menu->setPosition( isFramed() ? 2 : 0,
                      isFramed() ? 2 : 0 );
}

AWindow& PickUpWindow::show()
{
  if ( _picker && _container)
  {

    fillMenuWithItems();
    init();
    _menu->selectNext();

    TCODConsole& console = *TCODConsole::root;
    TCOD_key_t key;

    while( !(key.vk == TCODK_ESCAPE) &&
           !(TCODConsole::isWindowClosed()))
    {
      render(console);
      console.flush();

      TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

      switch ( key.vk )
      {
        case TCODK_DOWN:
        case TCODK_KP2:
        {
          _menu->selectNext();
          break;
        }
        case TCODK_UP:
        case TCODK_KP8:
        {
          _menu->selectPrevious();
          break;
        }
        case TCODK_ENTER:
        case TCODK_KPENTER:
        {
          choose();
          Engine::instance().render();
          break;
        }

        default:;
      }
    }

  }

  return *this;
}

void PickUpWindow::choose()
{
  if ( Actor* toPick = getSelectedActor() )
  {
    try
    {
      _afterPickUpAction(toPick->getName(),
                         ItemPicker(_picker, toPick, _container).pick());

      fillMenuWithItems();
    }
    catch( inventory_full& e )
    {
      _inventoryFullAction(e.getItemName());
    }
  }
}

Actor* PickUpWindow::getSelectedActor()
{
  Actor* toPick = nullptr;

  if ( AMenuItemPtr mItem = _menu->getSelectedItem() )
  {
    std::function<bool(Actor*)> filter = [&](Actor* a)
    {
      return a->getInstanceId() == mItem->getProperty<unsigned>("item_instance_id");
    };

    std::vector<Actor*> vectorToPick = _container->content(&filter);
    toPick =  vectorToPick.empty() ? nullptr : vectorToPick.front();
  }

  return toPick;
}

void PickUpWindow::fillMenuWithItems()
{
    _menu->removeAllItems();
    for(Actor* actor : _container->content(&_filterFunc))
    {
        AMenuItemPtr mItem( new ALabelMenuItem );
        mItem->setValue(actor->getName());
        mItem->setProperty<unsigned>("item_instance_id", actor->getInstanceId());
        _menu->addItem(mItem);
    }
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
  setTitle(title);
  return *this;
}

}}
