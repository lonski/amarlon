#ifndef CMDUSE_H
#define CMDUSE_H

#include "Command.h"

class CmdUse : public Command
{
public:
  CmdUse();

  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Map* map, Actor* executor);

private:
  Actor * selectItemToUse(Actor *executor);

};

#endif // CMDUSE_H
