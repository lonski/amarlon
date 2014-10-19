#include "CmdOpen.h"
#include <iostream>
#include "Utils/Utils.h"
#include <Utils/ItemPicker.h>
#include <algorithm>
#include "CmdPick.h"

CmdOpen::CmdOpen()
{
}

bool CmdOpen::accept(TCOD_key_t &key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'o' );
}

void CmdOpen::execute(Map *map, Actor *executor)
{
  int x = executor->getX();
  int y = executor->getY();

  int dx(0), dy(0);

  _dSelector.select(dx, dy);

  Actor* target = map->getFirstActor(x+dx, y+dy);
  if ( target )
  {
    //TODO: more generic openable, lock support

    //open doors
    if ( target->getId() == ActorType::DoorClosed)
    {
      target->morph(ActorType::DoorOpen);
      map->updateActorCell(target);
    }

    //display container
    if ( target->afContainer() )
    {
      CmdPick pickCommand;
      pickCommand.execute(target->afContainer(), executor);
    }
  }
}
