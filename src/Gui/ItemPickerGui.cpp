#include "ItemPickerGui.h"
#include <libtcod.hpp>
#include <Actor/actor.h>
#include <algorithm>
#include "Utils/glodef.h"

ItemPickerGui::ItemPickerGui(int width, int height)
  : _conWidth(width)
  , _conHeight(height)
  , _console(width, height)
{
}

void ItemPickerGui::render(const std::vector<Actor *> items, std::string title)
{
  renderConsoleFrame(title);
  renderItems(items);
  blitConsole();
}

void ItemPickerGui::renderConsoleFrame(std::string title)
{
  _console.setDefaultForeground(TCODColor(200,180,50));
  _console.printFrame(0, 0, _conWidth, _conHeight, true, TCOD_BKGND_DEFAULT, title.empty() ? NULL : title.c_str() );
}

void ItemPickerGui::renderItems(const std::vector<Actor *>& items)
{
  _console.setDefaultForeground(TCODColor::white);
  int shortcut='a';
  int row = 0;
  std::for_each(items.begin(), items.end(), [&](Actor* actor)
  {
    _console.print(2,++row,"(%c) %s", shortcut++, actor->getName().c_str());
  });
}

void ItemPickerGui::blitConsole()
{
  int posX = gloConsoleWidth  / 2 - _conWidth  / 2;
  int posY = gloConsoleHeight / 2 - _conHeight / 2;

  TCODConsole::blit(&_console, 0, 0, _conWidth, _conHeight, TCODConsole::root, posX, posY);
  TCODConsole::flush();
}

int ItemPickerGui::captureItemIndex(TCOD_keycode_t takeAllKey)
{
  int index = -2;

  TCOD_key_t key;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

  if (key.vk == TCODK_CHAR)
  {
    index = (int)key.c - (int)'a';
  }
  else if (key.vk == takeAllKey)
  {
    index = -1;
  }

  return index;
}


