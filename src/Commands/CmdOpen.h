#ifndef CMDOPEN_H
#define CMDOPEN_H

#include "Command.h"

namespace amarlon {

class CmdOpen : public Command
{
public:
  CmdOpen();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor* executor);

};

}

#endif // CMDOPEN_H
