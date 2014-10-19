#include "OpenableDoor.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include <iostream>

OpenableDoor::OpenableDoor()
{
}

bool OpenableDoor::open(Actor*)
{
  bool r = false;

  if (_owner->getId() == ActorType::DoorClosed)
  {
    if ( !isLocked() )
    {
      _owner->morph(ActorType::DoorOpen);
      r = true;
    }
    else
    {
      Gui::Root.message("The door are closed.");
    }
  }

  return r;
}

bool OpenableDoor::close(Actor*)
{
  bool r = false;

  if (_owner->getId() == ActorType::DoorOpen)
  {
    _owner->morph(ActorType::DoorClosed);
    r = true;
  }

  return r;
}
