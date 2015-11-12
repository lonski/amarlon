#ifndef CMDCLOSE_H
#define CMDCLOSE_H

#include "command.h"
#include "utils/direction_selector.h"

namespace amarlon {

class CmdClose : public Command
{
public:
  CmdClose();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMDCLOSE_H
