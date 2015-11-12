#ifndef CMD_GAME_MENU_H
#define CMD_GAME_MENU_H

#include "command.h"

namespace amarlon {

class CmdGameMenu : public Command
{
public:
  CmdGameMenu();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMD_GAME_MENU_H
