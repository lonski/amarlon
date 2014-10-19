#include "CommandExecutor.h"

CommandExecutor* CommandExecutor::_inst = nullptr;

CommandExecutor::CommandExecutor()
{
  for (int e = (int)CommandId::Null+1; e < (int)CommandId::End; ++e)
  {
    _commands.push_back( Command::create( (CommandId)e ) );
  }
}

bool CommandExecutor::executeCommand(TCOD_key_t &key, Map *map, Actor *executor)
{
  bool r = false;

  for (auto c = _commands.begin(); c != _commands.end(); ++c)
  {
    Command* cmd = *c;
    if ( cmd->accept(key) )
    {
      cmd->execute(map, executor);
      r = true;
      break;
    }
  }

  return r;
}

bool CommandExecutor::execute(TCOD_key_t& key, Map *map, Actor *executor)
{
  if ( _inst == nullptr)
    _inst = new CommandExecutor;

  return _inst->executeCommand(key, map, executor);
}
