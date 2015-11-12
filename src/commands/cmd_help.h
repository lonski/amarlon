#ifndef CMDHELP_H
#define CMDHELP_H

#include "command.h"

namespace amarlon {

class CmdHelp : public Command
{
public:
  CmdHelp();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMDHELP_H
