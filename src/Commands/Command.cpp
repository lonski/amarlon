#include "Command.h"
#include "CmdMove.h"
#include "CmdOpen.h"
#include "CmdFullscreen.h"
#include "CmdInventory.h"
#include "CmdPick.h"
#include "CmdDrop.h"
#include "CmdClose.h"
#include "CmdUse.h"

Command *Command::create(CommandId cmd)
{
  Command* c = NULL;

  switch(cmd)
  {
    case CommandId::Move: c = new CmdMoveOrAttack; break;
    case CommandId::Open: c = new CmdOpen; break;
    case CommandId::FullScreen: c = new CmdFullscreen; break;
    case CommandId::Inventory: c = new CmdInventory; break;
    case CommandId::Pick: c = new CmdPick; break;
    case CommandId::Drop: c = new CmdDrop; break;
    case CommandId::Close: c = new CmdClose; break;
    case CommandId::Use: c = new CmdUse; break;
    default: break;
  }

  return c;
}

