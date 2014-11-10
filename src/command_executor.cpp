#include "command_executor.h"

namespace amarlon {

CommandExecutor::CommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    _commands.push_back( Command::create( static_cast<CommandId>(e) ) );
  }
}

bool CommandExecutor::execute(TCOD_key_t &key, Actor *executor)
{
  bool r = false;

  for (auto c = _commands.begin(); c != _commands.end(); ++c)
  {
    Command* cmd = *c;
    if ( cmd->accept(key) )
    {
      cmd->execute(executor);
      r = true;
      break;
    }
  }

  return r;
}

}
