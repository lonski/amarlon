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

ActorFeature *OpenableDoor::clone()
{
  OpenableDoor* cloned = new OpenableDoor;
  cloned->setLockId( getLockId() );
  cloned->setLocked( isLocked() );

  return cloned;
}

bool OpenableDoor::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  OpenableDoor* crhs = dynamic_cast<OpenableDoor*>(rhs);

  if (crhs)
  {
    equal = (_lockId == crhs->_lockId);
  }

  return equal;
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
