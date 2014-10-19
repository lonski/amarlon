#ifndef COMMAND_H
#define COMMAND_H

#include <libtcod.hpp>
#include <iostream>
#include "Actor/Actor.h"
#include "World/Map.h"

enum class CommandId
{
  Null,
  Move,
  Open,
  FullScreen,
  Inventory,
  Pick,
  Drop,
  Close,
  End
};

class Command
{
public:
  Command() {}
  virtual ~Command() {}
  static Command* create(CommandId cmd);

  virtual bool accept(TCOD_key_t &key) = 0;
  virtual void execute(Map* map, Actor* executor) = 0;

};

#endif // COMMAND_H
