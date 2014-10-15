#ifndef CMDMOVE_H
#define CMDMOVE_H

#include "Command.h"

class CmdMoveOrAttack : public Command
{
public:
  CmdMoveOrAttack();
  bool accept(TCOD_key_t &key, Map* map, Actor* executor);

};

#endif // CMDMOVE_H
