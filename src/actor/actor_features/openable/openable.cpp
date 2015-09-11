#include "openable.h"
#include <openable_door.h>
#include <openable_container.h>
#include <amarlon_except.h>
#include <openable_factory.h>
#include <actor_descriptions.h>

namespace amarlon {

const ActorFeature::Type Openable::featureType = ActorFeature::OPENABLE;

Openable::Openable()
  : _locked(false)
  , _lockId(0)
{
}

OpenablePtr Openable::create(DescriptionPtr dsc)
{
  static OpenableFactory factory;
  return factory.produce( std::dynamic_pointer_cast<OpenableDescription>(dsc) );
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

void Openable::setLocked(bool locked)
{
  _locked = locked;
}

int Openable::getLockId() const
{
  return _lockId;
}

void Openable::setLockId(int lockId)
{
  _lockId = lockId;
}

void Openable::Creator::fillCommonOpenablePart(OpenablePtr openable, OpenableDescriptionPtr dsc)
{
  if ( openable != nullptr && dsc != nullptr )
  {
    openable->setLockId(dsc->lockId);
    openable->setLocked(dsc->locked);
  }
}

}
