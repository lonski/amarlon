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

class CommandExecutor
{
public:
  CommandExecutor();
  bool execute(TCOD_key_t &key);

private:
  std::vector<Command*> _commands;

};

typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;

}

#endif // COMMANDEXECUTOR_H
