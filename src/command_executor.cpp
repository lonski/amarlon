#include "command_executor.h"
#include "commands/command.h"

namespace amarlon {

CommandExecutor::CommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    _commands.push_back( Command::create( static_cast<CommandId>(e) ) );
  }
}

int CommandExecutor::execute(TCOD_key_t &key)
{
  for (auto c : _commands)
  {
    if (c->accept(key))
    {
      return c->execute();
    }
  }

  return 0;
}

}

