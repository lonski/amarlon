#ifndef CMDCLOSE_H
#define CMDCLOSE_H

#include "command.h"
#include "utils/direction_selector.h"

namespace amarlon {

class CmdClose : public Command
{
public:
  CmdClose();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute();

};

}

#endif // CMDCLOSE_H
