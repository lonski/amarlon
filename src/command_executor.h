#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <memory>
#include <vector>
#include <libtcod.hpp>


namespace amarlon {

class Actor;
class Map;
class Engine;
class Command;
typedef std::shared_ptr<Command> CommandPtr;

class CommandExecutor
{
public:
  CommandExecutor();
  int execute(const TCOD_key_t& key);

private:
  std::vector<CommandPtr> _commands;

};

typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;

class SystemCommandExecutor
{
public:
  SystemCommandExecutor();
  int execute(const TCOD_key_t& key);

private:
  std::vector<CommandPtr> _commands;

};

typedef std::shared_ptr<SystemCommandExecutor> SystemCommandExecutorPtr;

}

#endif // COMMANDEXECUTOR_H
