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

OpenablePtr Openable::create(OpenableType type)
{
  OpenablePtr o = nullptr;

  switch(type)
  {
    case OpenableType::OpenableDoor: o.reset( new OpenableDoor ); break;
    case OpenableType::OpenableContainer: o.reset( new OpenableContainer ); break;
    default:;
  }

  return o;
}

OpenablePtr Openable::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  OpenableDescriptionPtr oDsc = std::dynamic_pointer_cast<OpenableDescription>(dsc);
  OpenablePtr op = nullptr;

  if ( oDsc != nullptr )
  {
    op = Openable::create((oDsc->type));

    if ( op != nullptr )
    {
      op->setLockId(oDsc->lockId);
      op->_locked = oDsc->locked;
    }
  }else throw creation_error("Wrong openable description!");

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
