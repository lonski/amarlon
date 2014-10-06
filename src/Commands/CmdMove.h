#ifndef CMDMOVE_H
#define CMDMOVE_H

#include "command.h"

class CmdMoveOrAttack : public Command
{
public:
  CmdMoveOrAttack();
  bool accept(TCOD_key_t &key, Actor* executor, Map* map);

};

#endif // CMDMOVE_H
