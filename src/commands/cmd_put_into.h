#ifndef CMD_PUT_INTO_H
#define CMD_PUT_INTO_H

#include "commands/command.h"

namespace amarlon {

class CmdPutInto : public Command
{
public:  
  virtual bool accept(TCOD_key_t &key);
  virtual void execute();

};

}

#endif // CMD_PUT_INTO_H
