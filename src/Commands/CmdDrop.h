#ifndef CMDDROP_H
#define CMDDROP_H

#include "command.h"

class CmdDrop : public Command
{
public:
  CmdDrop();
  bool accept(TCOD_key_t &key, Map* map, Actor* executor);

};

#endif // CMDDROP_H
