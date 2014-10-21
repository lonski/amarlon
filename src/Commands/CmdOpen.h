#ifndef CMDOPEN_H
#define CMDOPEN_H

#include "Command.h"
#include "Utils/DirectionSelector.h"

class CmdOpen : public Command
{
public:
  CmdOpen();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Engine* engine, Actor* executor);

private:
  DirectionSelector _dSelector;

};

#endif // CMDOPEN_H
