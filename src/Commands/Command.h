#ifndef COMMAND_H
#define COMMAND_H

#include <libtcod.hpp>
#include <iostream>
#include "Actor/actor.h"
#include "World/map.h"

enum class CommandId
{
  Null,
  Move,
  OpenClose,
  FullScreen,
  Inventory,
  Pick,
  Drop,
  End
};

class Command
{
public:
  Command() {}
  virtual ~Command() {}
  static Command* create(CommandId cmd);

  virtual bool accept(TCOD_key_t &key, Map* map, Actor* executor) = 0;

};

#endif // COMMAND_H
