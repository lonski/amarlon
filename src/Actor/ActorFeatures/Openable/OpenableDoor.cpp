#include "OpenableDoor.h"
#include "Actor/Actor.h"
#include "Gui/Gui.h"
#include "Utils/Messenger.h"
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
      _owner->changeType(ActorType::DoorOpen);
      r = true;
    }
    else
    {
      Messenger::message()->actorIsLocked(_owner);
    }
  }

  return r;
}

bool OpenableDoor::close(Actor*)
{
  bool r = false;

  if (_owner->getId() == ActorType::DoorOpen)
  {
    _owner->changeType(ActorType::DoorClosed);
    _owner->afOpenable()->unlock();
    r = true;
  }

  return r;
}

bool OpenableDoor::lock()
{
  bool r = false;

  if (_owner->getId() == ActorType::DoorClosed)
  {
    r = Openable::lock();
  }

  return r;
}
