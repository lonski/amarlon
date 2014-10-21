#include "OpenableContainer.h"
#include "Commands/CmdPick.h"

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