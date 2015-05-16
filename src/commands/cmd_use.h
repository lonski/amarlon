#ifndef CMDUSE_H
#define CMDUSE_H

#include <vector>
#include <command.h>

namespace amarlon {

class CmdUse : public Command
{
public:
  CmdUse();

  virtual bool accept(TCOD_key_t &key);
  virtual void execute();

private:
  Actor* acquireItemToUse();
  std::vector<Actor*> getUsableItems();

};

}

#endif // CMDUSE_H
