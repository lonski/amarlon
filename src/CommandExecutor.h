#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <libtcod.hpp>
#include <vector>
#include "Commands/Command.h"

class Actor;
class Map;

class CommandExecutor
{
public:
  static bool execute(TCOD_key_t &key, Map* map, Actor* executor);
  bool executeCommand(TCOD_key_t &key, Map* map, Actor* executor);

private:
  CommandExecutor();
  static CommandExecutor* _inst;

  std::vector<Command*> _commands;

};

#endif // COMMANDEXECUTOR_H
