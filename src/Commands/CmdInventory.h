#ifndef CMDINVENTORY_H
#define CMDINVENTORY_H

#include <memory>
#include "Command.h"

namespace amarlon {

namespace gui{
  class InventoryWindow;
}

class CmdInventory : public Command
{
public:
  CmdInventory();
  virtual bool accept(TCOD_key_t &key);
  virtual void execute(Actor*);

};

}

#endif // CMDINVENTORY_H
