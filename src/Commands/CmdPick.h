#ifndef CMDPICK_H
#define CMDPICK_H

#include <functional>
#include "Command.h"

namespace amarlon {

class Container;

class CmdPick : public Command
{
public:
  CmdPick(Engine* engine);
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor* executor);

};

}

#endif // CMDPICK_H
