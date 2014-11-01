#include "OpenableContainer.h"
#include <Gui/pick_up_window.h>
#include <Actor/Actor.h>

namespace amarlon {

OpenableContainer::OpenableContainer()
{
}

bool OpenableContainer::open(Actor *executor)
{
  bool r = false;

  if ( _owner->afContainer() )
  {
    gui::PickUpWindow pickuper(*executor, *_owner->afContainer(), [](Actor* a){ return a->afPickable();});
    pickuper.show();

    r = true;
  }

  return r;
}

bool OpenableContainer::close(Actor*)
{
  return true;
}

ActorFeature *OpenableContainer::clone()
{
  OpenableContainer* cloned = new OpenableContainer;
  cloned->setLockId( getLockId() );
  cloned->setLocked( isLocked() );

  return cloned;
}

bool OpenableContainer::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  OpenableContainer* crhs = dynamic_cast<OpenableContainer*>(rhs);

  if (crhs)
  {
    equal = (_lockId == crhs->_lockId);
  }

  return equal;
}

}
