#ifndef CMDFULLSCREEN_H
#define CMDFULLSCREEN_H

#include "command.h"

namespace amarlon {

class CmdFullscreen : public Command
{
public:
  CmdFullscreen();
  virtual bool accept(TCOD_key_t &key);
  virtual int execute();

};

}

#endif // CMDFULLSCREEN_H
