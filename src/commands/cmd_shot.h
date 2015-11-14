#ifndef CMD_SHOT_H
#define CMD_SHOT_H

#include "command.h"

namespace amarlon {

class CmdShot : public Command
{
public:
  CmdShot();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMD_SHOT_H
