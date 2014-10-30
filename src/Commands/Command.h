#ifndef COMMAND_H
#define COMMAND_H

#include <libtcod.hpp>
#include <iostream>
#include "Actor/Actor.h"

namespace amarlon {

class Engine;

enum class CommandId
{
  Null,
  Move,
  Open,
  FullScreen,
  Inventory,
  Pick,
  Close,
  Use,
  End
};

class Command
{
public:
  Command() {}
  virtual ~Command() {}
  static Command* create(CommandId cmd);

  virtual bool accept(TCOD_key_t &key) = 0;
  virtual void execute(Engine* engine, Actor* executor) = 0;

};

}

#endif // COMMAND_H
