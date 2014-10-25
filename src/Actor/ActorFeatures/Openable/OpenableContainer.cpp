#include "OpenableContainer.h"
#include "Commands/CmdPick.h"

namespace amarlon {

OpenableContainer::OpenableContainer()
{
}

bool OpenableContainer::open(Actor *executor)
{
  bool r = false;

  if ( _owner->afContainer() )
  {
    CmdPick pickCommand;
    pickCommand.execute(_owner->afContainer(), executor);

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
