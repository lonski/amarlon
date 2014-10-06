#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <libtcod.hpp>
#include <vector>
#include "Commands/command.h"

class Actor;
class Map;

class CommandExecutor
{
public:
  CommandExecutor();

  bool execute(TCOD_key_t &key, Actor* executor, Map* map);

private:
  std::vector<Command*> _commands;

};

#endif // COMMANDEXECUTOR_H
