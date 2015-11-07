#ifndef CMD_TALK_H
#define CMD_TALK_H

#include <vector>
#include <command.h>

namespace amarlon {

class Dialog;
class Choice;

class CmdTalk : public Command
{
public:
  CmdTalk();

  virtual bool accept(TCOD_key_t &key);
  virtual int execute();

private:
  std::pair<Dialog, Choice> display(const Dialog& d);

};

}

#endif // CMD_TALK_H
