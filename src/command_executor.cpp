#include "command_executor.h"
#include "commands/command.h"
#include <game_timer.h>
#include <iostream>

namespace amarlon {

CommandExecutor::CommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    _commands.push_back( Command::create( static_cast<CommandId>(e) ) );
  }
}

bool CommandExecutor::execute(TCOD_key_t &key)
{  
  bool r = false;

  for (auto c : _commands)
  {
    if (c->accept(key))
    {
      TimeStop stop;

      c->execute();
      r = true;
      break;
    }
  }

  return r;
}

}
