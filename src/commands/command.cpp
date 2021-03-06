#include "command.h"
#include "cmd_move.h"
#include "cmd_open.h"
#include "cmd_inventory.h"
#include "cmd_pick.h"
#include "cmd_close.h"
#include "cmd_use.h"
#include "cmd_help.h"
#include "cmd_put_into.h"
#include "cmd_look.h"
#include "cmd_cast.h"
#include "cmd_spellbook.h"
#include "cmd_inspect.h"
#include "cmd_rest.h"
#include "cmd_use_skill.h"
#include "cmd_talk.h"
#include "cmd_shot.h"

#include "cmd_fullscreen.h"
#include "cmd_game_menu.h"
#include "cmd_debug.h"

namespace amarlon {

CommandPtr Command::create(CommandId cmd)
{
  CommandPtr c;

  switch(cmd)
  {
    case CommandId::Move:       c.reset( new CmdMove ); break;
    case CommandId::Open:       c.reset( new CmdOpen         ); break;
    case CommandId::Inventory:  c.reset( new CmdInventory    ); break;
    case CommandId::Pick:       c.reset( new CmdPick         ); break;
    case CommandId::Close:      c.reset( new CmdClose        ); break;
    case CommandId::Use:        c.reset( new CmdUse          ); break;
    case CommandId::Help:       c.reset( new CmdHelp         ); break;
    case CommandId::PutInto:    c.reset( new CmdPutInto      ); break;
    case CommandId::Look:       c.reset( new CmdLook         ); break;
    case CommandId::Cast:       c.reset( new CmdCast         ); break;
    case CommandId::Spellbook:  c.reset( new CmdSpellbook    ); break;
    case CommandId::Inspect:    c.reset( new CmdInspect      ); break;
    case CommandId::Rest:       c.reset( new CmdRest         ); break;
    case CommandId::UseSkill:   c.reset( new CmdUseSkill     ); break;
    case CommandId::Talk:       c.reset( new CmdTalk         ); break;
    case CommandId::Shot:       c.reset( new CmdShot         ); break;

    default: break;
  }

  return c;
}

CommandPtr Command::createSystemCommand(CommandId cmd)
{
  CommandPtr c;

  switch(cmd)
  {
    case CommandId::FullScreen: c.reset( new CmdFullscreen   ); break;
    case CommandId::GameMenu:   c.reset( new CmdGameMenu     ); break;
    case CommandId::Debug:      c.reset( new CmdDebug        ); break;

    default: break;
  }

  return c;
}

}

