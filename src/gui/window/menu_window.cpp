#include "menu_window.h"
#include <game_timer.h>

namespace amarlon { namespace gui {

MenuWindow::MenuWindow()
  : _menu( new AMenu )
{
  addWidget(_menu);
}

AWindow& MenuWindow::show()
{
  _visible = true;
  TCODConsole& console = *TCODConsole::root;
  TCOD_key_t key;

  init();
  _menu->selectNext();

  while( !(key.vk == TCODK_ESCAPE) &&
         !(key.vk == TCODK_ENTER ) &&
         !(key.vk == TCODK_KPENTER) &&
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

      default:;
    }

  }

  if ( key.vk == TCODK_ESCAPE )
  {
    _menu->deselect();
  }

  _visible = false;
  return *this;
}

void MenuWindow::init()
{
  setWidth ( std::max( _menu->getWidth() + 4, getWidth() ) );
  setHeight( std::max( _menu->getHeight() + 4, getHeight() ) );

  _menu->setPosition( isFramed() ? 2 : 0,
                      isFramed() ? 2 : 0 );
}

AWindow &MenuWindow::setDefaults()
{
  _menu->removeAllItems();

  setTitle("");
  setFrameColor(TCODColor::darkerOrange);
  setTitleColor(TCODColor::lighterOrange);

  setHeight(2);
  setWidth(40);
  setFrame(true);

  return *this;
}

void MenuWindow::addMenuItem(AMenuItemPtr item)
{
  _menu->addItem( item );
}

AMenuItemPtr MenuWindow::getSelectedItem()
{
  return _menu->getSelectedItem();
}

}}
