#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <libtcod.hpp>
#include <vector>
#include "Commands/Command.h"

class Actor;
class Map;
class Engine;

class CommandExecutor
{
public:
  static bool execute(TCOD_key_t &key, Engine* engine, Actor* executor);
  bool executeCommand(TCOD_key_t &key, Engine *engine, Actor* executor);

private:
  CommandExecutor();
  static CommandExecutor* _inst;

  std::vector<Command*> _commands;

};

#endif // COMMANDEXECUTOR_H
