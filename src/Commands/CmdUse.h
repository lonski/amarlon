#ifndef CMDUSE_H
#define CMDUSE_H

#include "Command.h"

namespace amarlon {

class CmdUse : public Command
{
public:
  CmdUse();

  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Engine* engine, Actor* executor);

};

}

#endif // CMDUSE_H
