#include "CmdOpen.h"
#include <iostream>
#include "Utils/Utils.h"
#include <Utils/ItemPicker.h>
#include <algorithm>

CmdOpenClose::CmdOpenClose()
{
}

bool CmdOpenClose::accept(TCOD_key_t &key, Map *map, Actor *executor)
{
  bool accepted = ( key.vk == TCODK_CHAR && (key.c == 'o' || key.c == 'c') );
  bool open = key.c == 'o';

  if (accepted)
  {
    int x = executor->getX();
    int y = executor->getY();

    int dx(0), dy(0);
    selectDirection(dx, dy);

    Actor* target = map->getFirstActor(x+dx, y+dy);
    if ( target )
    {      
      //TODO: more generic openable, lock support
      if ( open )
      {
        //open doors
        if ( target->getId() == ActorType::DoorClosed)
        {
          target->morph(ActorType::DoorOpen);
          map->updateActorCell(target);
        }

        //display container
        if ( target->afContainer() )
        {
          ItemPicker picker(target->afContainer()->content(), executor);
          std::vector<Actor*> itemsPicked = picker.pick(true);

          std::for_each(itemsPicked.begin(), itemsPicked.end(), [&](Actor* a)
          {
            target->afContainer()->remove(a);
          });
        }

      }
      else
      {
        //close doors
        if ( target->getId() == ActorType::DoorOpen)
        {
          target->morph(ActorType::DoorClosed);
          map->updateActorCell(target);
        }
      }


    }
  }

  return accepted;
}

void CmdOpenClose::selectDirection(int& dx, int& dy)
{
  TCOD_key_t lastKey;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,NULL, true);

  handleDirectionKey(lastKey, dx, dy);
}
