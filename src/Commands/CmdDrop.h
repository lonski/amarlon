#ifndef CMDDROP_H
#define CMDDROP_H

#include "Command.h"

class CmdDrop : public Command
{
public:
  CmdDrop();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Engine* engine, Actor* executor);

};

#endif // CMDDROP_H
