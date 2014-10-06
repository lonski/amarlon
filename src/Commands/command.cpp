#include "command.h"
#include "CmdMove.h"

Command *Command::create(CommandId cmd)
{
  Command* c = NULL;

  switch(cmd)
  {
    case CommandId::Move: c = new CmdMoveOrAttack; break;
    default: break;
  }

  return c;
}
