#ifndef CMDFULLSCREEN_H
#define CMDFULLSCREEN_H

#include "Command.h"

namespace amarlon {

class CmdFullscreen : public Command
{
public:
  CmdFullscreen();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Engine* engine, Actor* executor);

};

}

#endif // CMDFULLSCREEN_H
