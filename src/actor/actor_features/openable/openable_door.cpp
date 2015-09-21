#include "openable_door.h"
#include <actor.h>
#include <gui.h>
#include <message_box.h>
#include <actor_descriptions.h>

namespace amarlon {

OpenableDoor::OpenableDoor()
{
}

bool OpenableDoor::open(ActorPtr)
{
  bool r = false;

  if (getOwner().lock()->getType() == ActorType::DoorClosed)
  {
    if ( !isLocked() )
    {
      getOwner().lock()->setType(ActorType::DoorOpen);
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

  if (getOwner().lock()->getType() == ActorType::DoorOpen)
  {
    getOwner().lock()->setType(ActorType::DoorClosed);
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

bool OpenableDoor::isEqual(ActorFeaturePtr rhs) const
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
  if (owner && owner->getType() == ActorType::DoorClosed)
  {
    r = Openable::lock();
  }

  return r;
}

OpenablePtr OpenableDoor::Creator::create(OpenableDescriptionPtr dsc)
{
  OpenablePtr op = nullptr;

  OpenableDoorDescriptionPtr doorDsc = std::dynamic_pointer_cast<OpenableDoorDescription>(dsc);
  if ( doorDsc != nullptr )
  {
    op = std::make_shared<OpenableDoor>();
    Openable::Creator::fillCommonOpenablePart(op, dsc);
  }

  return op;
}

}
