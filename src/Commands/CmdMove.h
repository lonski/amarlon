#ifndef CMDMOVE_H
#define CMDMOVE_H

#include "Command.h"

namespace amarlon {

class CmdMoveOrAttack : public Command
{
public:
  CmdMoveOrAttack();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Engine* engine, Actor* executor);

  virtual void setDirection(int dx, int dy);

private:
  int _dx;
  int _dy;

};

}

#endif // CMDMOVE_H
