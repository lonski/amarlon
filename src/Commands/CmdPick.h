#ifndef CMDPICK_H
#define CMDPICK_H

#include "Command.h"

class Container;

class CmdPick : public Command
{
public:
  CmdPick();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Map* map, Actor* executor);
  virtual void execute(Container *container, Actor* executor, bool forceGui = true);

};

#endif // CMDPICK_H
