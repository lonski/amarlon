#ifndef CMD_SPELLBOOK_H
#define CMD_SPELLBOOK_H

#include "command.h"

namespace amarlon {

class CmdSpellbook : public Command
{
public:
  CmdSpellbook();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMD_SPELLBOOK_H
