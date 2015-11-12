#include "command_executor.h"
#include "commands/command.h"

namespace amarlon {

CommandExecutor::CommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    auto c = Command::create( static_cast<CommandId>(e));
    if (c) _commands.push_back( c );
  }
}

int CommandExecutor::execute(const TCOD_key_t& key)
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

SystemCommandExecutor::SystemCommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    auto c = Command::createSystemCommand( static_cast<CommandId>(e));
    if (c) _commands.push_back( c );
  }
}

int SystemCommandExecutor::execute(const TCOD_key_t& key)
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

