#ifndef CMDINVENTORY_H
#define CMDINVENTORY_H

#include "Command.h"

class CmdInventory : public Command
{
public:
  CmdInventory();
  bool accept(TCOD_key_t &key, Map* map, Actor* executor);

};

#endif // CMDINVENTORY_H
