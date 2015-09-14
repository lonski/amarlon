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
  virtual int execute();

private:
  ActorPtr acquireItemToUse();
  std::vector<ActorPtr> getUsableItems();

};

}

#endif // CMDUSE_H
