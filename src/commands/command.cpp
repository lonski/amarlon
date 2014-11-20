#include "command.h"
#include "cmd_move.h"
#include "cmd_open.h"
#include "cmd_fullscreen.h"
#include "cmd_inventory.h"
#include "cmd_pick.h"
#include "cmd_close.h"
#include "cmd_use.h"
#include "cmd_help.h"
#include "cmd_put_into.h"
#include "cmd_look.h"

namespace amarlon {

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
    case CommandId::Close: c = new CmdClose; break;
    case CommandId::Use: c = new CmdUse; break;
    case CommandId::Help: c = new CmdHelp; break;
    case CommandId::PutInto: c = new CmdPutInto; break;
    case CommandId::Look: c = new CmdLook; break;
    default: break;
  }

  return c;
}

}
