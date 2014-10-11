#ifndef CMDPICK_H
#define CMDPICK_H

#include "command.h"

class CmdPick : public Command
{
public:
  CmdPick();
  bool accept(TCOD_key_t &key, Map* map, Actor* executor);

};

#endif // CMDPICK_H
