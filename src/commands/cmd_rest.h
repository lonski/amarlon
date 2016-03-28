#ifndef CMD_REST_H
#define CMD_REST_H

#include "command.h"

namespace amarlon {

class CmdRest : public Command
{
public:
  CmdRest();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

private:
  int _restHours;

  void fadeIn();
  void fadeOut();
  void tickTime();
  void restoreCharacters();

};

}


#endif // CMD_REST_H
