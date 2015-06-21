#include "openable.h"
#include "openable_door.h"
#include "openable_container.h"
#include "amarlon_except.h"

namespace amarlon {

const ActorFeature::Type Openable::featureType = ActorFeature::OPENABLE;

Openable::Openable()
  : _locked(false)
  , _lockId(0)
{
}

OpenablePtr Openable::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */

  OpenablePtr op = nullptr;
  OpenableDescriptionPtr oDsc = std::dynamic_pointer_cast<OpenableDescription>(dsc);
  if ( oDsc )
  {
    //door?
    OpenableDoorDescriptionPtr doorDsc = std::dynamic_pointer_cast<OpenableDoorDescription>(dsc);
    if ( doorDsc != nullptr )
    {
      op = std::make_shared<OpenableDoor>();
    }
    //container?
    else
    {
      OpenableContainerDescriptionPtr contDsc = std::dynamic_pointer_cast<OpenableContainerDescription>(dsc);
      if ( contDsc )
      {
        op = std::make_shared<OpenableContainer>();
      }
    }

    //common part
    if ( op != nullptr )
    {
      op->setLockId(oDsc->lockId);
      op->_locked = oDsc->locked;
    }
  }

  return op;
}

ActorFeature::Type Openable::getType()
{
  return featureType;
}

bool Openable::lock()
{
  _locked = true;
  return _locked;
}

bool Openable::unlock()
{
  _locked = false;
  return !_locked;
}

bool Openable::isLocked() const
{
  return _locked;
}

int Openable::getLockId() const
{
  return _lockId;
}

void Openable::setLockId(int lockId)
{
  _lockId = lockId;
}

}
