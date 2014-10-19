#include "Openable.h"
#include "OpenableDoor.h"
#include "OpenableContainer.h"

Openable::Openable()
  :_locked(false)
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

