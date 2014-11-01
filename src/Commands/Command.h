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
  Command(Engine* engine): _engine(engine) {}
  virtual ~Command() {}
  static Command* create(CommandId cmd, Engine* engine);

  virtual bool accept(TCOD_key_t &key) = 0;
  virtual void execute(Actor* executor) = 0;

protected:
  Engine* _engine;

};

}

#endif // COMMAND_H
