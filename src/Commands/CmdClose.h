#ifndef CMDCLOSE_H
#define CMDCLOSE_H

#include "Command.h"
#include "Utils/DirectionSelector.h"

namespace amarlon {

class CmdClose : public Command
{
public:
  CmdClose();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor* executor);

private:
  DirectionSelector _dSelector;

};

}

#endif // CMDCLOSE_H
