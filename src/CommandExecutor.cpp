#include "CommandExecutor.h"

CommandExecutor::CommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    _commands.push_back( Command::create( (CommandId)e ) );
  }
}

bool CommandExecutor::execute(TCOD_key_t& key, Actor *executor, Map *map)
{
  bool r = false;

  for (auto c = _commands.begin(); c != _commands.end(); ++c)
  {
    Command* cmd = *c;
    if ( cmd->accept(key, executor, map) )
    {
      r = true;
      break;
    }
  }

  return r;
}
