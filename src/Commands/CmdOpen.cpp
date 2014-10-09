#include "CmdOpen.h"
#include <iostream>

CmdOpenClose::CmdOpenClose()
{
}

bool CmdOpenClose::accept(TCOD_key_t &key, Actor *executor, Map *map)
{
  bool accepted = ( key.vk == TCODK_CHAR && (key.c == 'o' || key.c == 'c') );
  bool open = key.c == 'o';

  if (accepted)
  {
    int x = executor->getX();
    int y = executor->getY();

    int dx(0), dy(0);
    selectDirection(dx, dy);

    Actor* target = map->getActor(x+dx, y+dy);
    if ( target )
    {
      if ( target->getId() == ActorType::Drzwi_Zamkniete && open )
      {
        target->morph(ActorType::Drzwi_Otwarte);
      }

      if ( target->getId() == ActorType::Drzwi_Otwarte && !open )
      {
        target->morph(ActorType::Drzwi_Zamkniete);
      }
    }
  }

  return accepted;
}

void CmdOpenClose::selectDirection(int& dx, int& dy)
{
  TCOD_key_t lastKey;
  while ( !TCODConsole::isWindowClosed() )
  {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,NULL);

    switch(lastKey.vk)
    {
      case TCODK_KP7 : dy = -1; dx = -1; break;
      case TCODK_KP9 : dy = -1; dx =  1; break;
      case TCODK_KP1 : dy =  1; dx = -1; break;
      case TCODK_KP3 : dy =  1; dx =  1; break;
      case TCODK_KP8 : dy = -1; dx =  0; break;
      case TCODK_KP4 : dy =  0; dx = -1; break;
      case TCODK_KP2 : dy =  1; dx =  0; break;
      case TCODK_KP6 : dy =  0; dx =  1; break;
      default:;
    }

    if ( dx != 0 || dy != 0)
      break;
  }
}
