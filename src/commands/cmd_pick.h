#ifndef CMDPICK_H
#define CMDPICK_H

#include <functional>
#include "command.h"

namespace amarlon {

class Inventory;

class CmdPick : public Command
{
public:
  CmdPick();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute();

};

}

#endif // CMDPICK_H
