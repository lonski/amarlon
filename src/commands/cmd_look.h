#ifndef CMD_LOOK_H
#define CMD_LOOK_H

#include <command.h>

namespace amarlon {

class CmdLook : public Command
{
public:
  CmdLook() = default;
  virtual bool accept(TCOD_key_t &key);
  virtual void execute();

};

}

#endif // CMD_LOOK_H
