#ifndef CMDUSE_H
#define CMDUSE_H

#include "Command.h"

namespace amarlon {

class CmdUse : public Command
{
public:
  CmdUse(Engine* engine);

  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor* executor);

private:
  Actor * acquireItemToUse(Actor *executor, Engine *engine);

};

}

#endif // CMDUSE_H
