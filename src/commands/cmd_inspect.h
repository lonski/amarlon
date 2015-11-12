#ifndef CMD_INSPECT_H
#define CMD_INSPECT_H

#include "command.h"

namespace amarlon {

class CmdInspect : public Command
{
public:
  CmdInspect();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMD_INSPECT_H
