#ifndef CMDMOVE_H
#define CMDMOVE_H

#include "command.h"

namespace amarlon {

class CmdMove : public Command
{
public:
  CmdMove();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

  virtual void setDirection(int dx, int dy);

private:
  int _dx;
  int _dy;

  ActorPtr getActorOnPath();
  void talkAction(ActorPtr actor);

};

}

#endif // CMDMOVE_H
