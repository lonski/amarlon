#include "ItemPickerGui.h"
#include <libtcod.hpp>
#include <Actor/actor.h>
#include <algorithm>

ItemPickerGui::ItemPickerGui()
{
}

void ItemPickerGui::pick(const std::vector<Actor *> items, std::string title)
{
  static const int conWidth=50;
  static const int conHeight=28;
  static TCODConsole con(conWidth,conHeight);

  // display the inventory frame
  con.setDefaultForeground(TCODColor(200,180,50));
  con.printFrame(0, 0, conWidth, conHeight, true, TCOD_BKGND_DEFAULT, title.empty() ? NULL : title.c_str() );

  // display the items with their keyboard shortcut
  con.setDefaultForeground(TCODColor::white);
  int shortcut='a';
  int y = 1;
  std::for_each(items.begin(), items.end(), [&](Actor* actor)
  {
    con.print(2,y++,"(%c) %s", shortcut++, actor->getName().c_str());
  });

  // blit the inventory console on the root console
  TCODConsole::blit(&con, 0, 0, conWidth, conHeight, TCODConsole::root, 50 - conWidth/2, 30 - conHeight/2 );
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


