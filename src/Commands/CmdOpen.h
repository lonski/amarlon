#ifndef CMDOPEN_H
#define CMDOPEN_H

#include "command.h"

class CmdOpenClose : public Command
{
public:
  CmdOpenClose();
  bool accept(TCOD_key_t &key, Actor* executor, Map* map);

private:
  void selectDirection(int &dx, int &dy);

};

#endif // CMDOPEN_H
