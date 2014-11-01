#include "Command.h"
#include "CmdMove.h"
#include "CmdOpen.h"
#include "CmdFullscreen.h"
#include "CmdInventory.h"
#include "CmdPick.h"
#include "CmdClose.h"
#include "CmdUse.h"

namespace amarlon {

Command *Command::create(CommandId cmd, Engine *engine)
{
  Command* c = NULL;

  switch(cmd)
  {
    case CommandId::Move: c = new CmdMoveOrAttack(engine); break;
    case CommandId::Open: c = new CmdOpen(engine); break;
    case CommandId::FullScreen: c = new CmdFullscreen(engine); break;
    case CommandId::Inventory: c = new CmdInventory(engine); break;
    case CommandId::Pick: c = new CmdPick(engine); break;
    case CommandId::Close: c = new CmdClose(engine); break;
    case CommandId::Use: c = new CmdUse(engine); break;
    default: break;
  }

  return c;
}

}
