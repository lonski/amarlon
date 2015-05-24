#include "openable_door.h"
#include "actor/actor.h"
#include "gui/gui.h"
#include "gui/message_box.h"

namespace amarlon {

OpenableDoor::OpenableDoor()
{
}

bool OpenableDoor::open(ActorPtr)
{
  bool r = false;

  if (getOwner().lock()->getId() == ActorType::DoorClosed)
  {
    if ( !isLocked() )
    {
      getOwner().lock()->changeType(ActorType::DoorOpen);
      r = true;
    }
    else
    {
      gui::msgBox("The "+getOwner().lock()->getName()+" is locked.", gui::MsgType::Warning);
    }
  }

  return r;
}

bool OpenableDoor::close(ActorPtr)
{
  bool r = false;

  if (getOwner().lock()->getId() == ActorType::DoorOpen)
  {
    getOwner().lock()->changeType(ActorType::DoorClosed);
    getOwner().lock()->getFeature<Openable>()->unlock();
    r = true;
  }

  return r;
}

ActorFeaturePtr OpenableDoor::clone()
{
  OpenableDoorPtr cloned( new OpenableDoor );
  cloned->setLockId( getLockId() );
  cloned->_locked = isLocked();

  return cloned;
}

bool OpenableDoor::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  OpenableDoorPtr crhs = std::dynamic_pointer_cast<OpenableDoor>(rhs);

  if (crhs != nullptr)
  {
    equal = (_lockId == crhs->_lockId);
  }

  return equal;
}

bool OpenableDoor::lock()
{
  bool r = false;

  ActorPtr owner = getOwner().lock();
  if (owner && owner->getId() == ActorType::DoorClosed)
  {
    r = Openable::lock();
  }

  return r;
}

}
