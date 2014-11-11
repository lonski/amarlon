#ifndef CMD_PUT_INTO_H
#define CMD_PUT_INTO_H

#include <Commands/Command.h>
#include <utils/direction_selector.h>

namespace amarlon {

class CmdPutInto : public Command
{
public:  
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor* executor);

private:
  DirectionSelector _dSelector;

};

}

#endif // CMD_PUT_INTO_H
