#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <memory>
#include <vector>
#include <libtcod.hpp>
#include "Commands/Command.h"

namespace amarlon {

class Actor;
class Map;
class Engine;

class CommandExecutor
{
public:
  CommandExecutor(Engine *engine);
  bool execute(TCOD_key_t &key, Actor* executor);

private:
  std::vector<Command*> _commands;

};

typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;

}

#endif // COMMANDEXECUTOR_H
