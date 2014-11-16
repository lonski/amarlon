#include "Openable.h"
#include "OpenableDoor.h"
#include "OpenableContainer.h"
#include <amarlon_except.h>

namespace amarlon {

const ActorFeature::Type Openable::featureType = ActorFeature::OPENABLE;

Openable::Openable()
  : _locked(false)
  , _lockId(0)
{
}

Openable *Openable::create(OpenableType type)
{
  Openable* o = nullptr;

  switch(type)
  {
    case OpenableType::OpenableDoor: o = new OpenableDoor; break;
    case OpenableType::OpenableContainer: o = new OpenableContainer; break;
    default:;
  }

  return o;
}

Openable *Openable::create(Description* dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  OpenableDescription* oDsc = dynamic_cast<OpenableDescription*>(dsc);
  Openable* op = nullptr;

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

bool Openable::lock()
{
  _locked = true;
  return true;
}

bool Openable::unlock()
{
  _locked = false;
  return true;
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

void Openable::setLocked(bool locked)
{
  _locked = locked;
}

}
