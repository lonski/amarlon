#ifndef CMDINVENTORY_H
#define CMDINVENTORY_H

#include "command.h"

namespace amarlon {

namespace gui{
  class InventoryWindow;
}

class CmdInventory : public Command
{
public:
  CmdInventory();
  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

};

}

#endif // CMDINVENTORY_H
