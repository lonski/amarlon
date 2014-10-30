#include "Openable.h"
#include "OpenableDoor.h"
#include "OpenableContainer.h"

namespace amarlon {

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

Openable *Openable::create(const OpenableDescription &dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  Openable* op = Openable::create((dsc.type));

  if ( op != nullptr )
  {
    op->setLockId(dsc.lockId);
    op->_locked = dsc.locked;
  }

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
