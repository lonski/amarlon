#ifndef CMD_LOOK_H
#define CMD_LOOK_H

#include "command.h"

namespace amarlon {

class CmdLook : public Command
{
public:
  CmdLook() = default;
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMD_LOOK_H
