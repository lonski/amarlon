#include "ItemPickerWindow.h"
#include "Utils/glodef.h"
#include "Actor/Actor.h"
#include <libtcod.hpp>
#include <algorithm>
#include <iostream>

namespace amarlon {

ItemPickerGui::ItemPickerGui(std::string title, int width, int height)
  : _title(title)
  , _conWidth(width)
  , _conHeight(height)
  , _console(width, height)
  , _items(nullptr)
  , _index(0)
{
}

int ItemPickerGui::pick(const std::vector<Actor *> &items)
{
  TCOD_key_t key;

  _items = &items;
  _index = 0;

  while(_items != nullptr       &&
        key.vk != TCODK_ENTER   && //accept
        key.vk != TCODK_KPENTER && //accept
        key.vk != TCODK_SPACE   && //take all
        key.vk != TCODK_ESCAPE  && //cancel
        !TCODConsole::isWindowClosed())
  {
    render();
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
    handlePressedKey(key);
  }

  return _index;
}

void ItemPickerGui::render()
{
  renderConsoleFrame(_title);
  renderItems();
  blitConsole();
}

void ItemPickerGui::renderConsoleFrame(std::string title)
{
  _console.setDefaultForeground(TCODColor(200,180,50));
  _console.printFrame(0, 0, _conWidth, _conHeight, true, TCOD_BKGND_DEFAULT,
                      title.empty() ? NULL : title.c_str() );
}

void ItemPickerGui::renderItems()
{
  int row = 0;
  int amount = 1;
  std::for_each(_items->begin(), _items->end(), [&](Actor* actor)
  {
    amount = actor->afPickable()->getAmount();

    _console.setDefaultForeground( row == _index ? TCODColor::white : TCODColor::lighterGrey);    

    if (amount > 1)
      _console.print(2,++row,"%s (%d)", actor->getName().c_str(), amount);
    else
      _console.print(2,++row,"%s", actor->getName().c_str());
  });
}

void ItemPickerGui::blitConsole()
{
  int posX = gloConsoleWidth  / 2 - _conWidth  / 2;
  int posY = gloConsoleHeight / 2 - _conHeight / 2;

  TCODConsole::blit(&_console, 0, 0, _conWidth, _conHeight, TCODConsole::root, posX, posY);
  TCODConsole::flush();
}

void ItemPickerGui::handlePressedKey(TCOD_key_t key)
{
  switch( key.vk )
  {
    case TCODK_DOWN:
    case TCODK_KP2:
    {
      if ( _index < (int)_items->size()-1 ) ++_index;
    }
    break;

    case TCODK_UP:
    case TCODK_KP8:
    {
      if ( _index > 0 ) --_index;
    }
    break;

    case TCODK_SPACE:
    {
      _index = -1;
    }
    break;

    case TCODK_ESCAPE:
    {
      _index = -2;
    }
    break;

    default:;
  }
}

void ItemPickerGui::setTitle(const std::string &title)
{
  _title = title;
}

}
