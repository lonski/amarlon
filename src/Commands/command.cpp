#include "command.h"
#include "CmdMove.h"
#include "CmdOpen.h"
#include "CmdFullscreen.h"

Command *Command::create(CommandId cmd)
{
  Command* c = NULL;

  switch(cmd)
  {
    case CommandId::Move: c = new CmdMoveOrAttack; break;
    case CommandId::OpenClose: c = new CmdOpenClose; break;
    case CommandId::FullScreen: c = new CmdFullscreen; break;
    default: break;
  }

  return c;
}
