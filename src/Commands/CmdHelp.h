#ifndef CMDHELP_H
#define CMDHELP_H

#include "Command.h"

namespace amarlon {

class CmdHelp : public Command
{
public:
  CmdHelp();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor* executor);

};

}

#endif // CMDHELP_H
