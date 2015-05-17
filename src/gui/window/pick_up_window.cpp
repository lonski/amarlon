#include "pick_up_window.h"
#include <alabel_menu_item.h>
#include <message_box.h>
#include <amount_window.h>
#include <container.h>
#include <item_action.h>
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
  _filterFunc = [](ActorPtr){return true;};

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
           !(TCODConsole::isWindowClosed()) &&
           _menu->getItemCount() > 0)
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
          _menu->selectNext();
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
  if ( ActorPtr toPick = getSelectedActor() )
  {
    try
    {
      _afterPickUpAction(toPick->getName(),
                         ItemAction(_picker, toPick, _container).pick());

      fillMenuWithItems();
    }
    catch( inventory_full& e )
    {
      _inventoryFullAction(e.getItemName());
    }
  }
}

ActorPtr PickUpWindow::getSelectedActor()
{
  AMenuItemPtr mItem = _menu->getSelectedItem();
  return mItem ? mItem->getObject<Actor>() : ActorPtr();
}

void PickUpWindow::fillMenuWithItems()
{
  _menu->fill<Actor>( _container->content(&_filterFunc), getItemNameAndAmount );
}

PickUpWindow& PickUpWindow::setPicker(ActorPtr picker)
{
  _picker = picker;
  return *this;
}

PickUpWindow& PickUpWindow::setContainer(ContainerPtr container)
{
  _container = container;
  return *this;
}

PickUpWindow& PickUpWindow::setFilterFunction(std::function<bool(ActorPtr)> fun)
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
