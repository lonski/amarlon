#include "cmd_look.h"

namespace amarlon {

bool CmdLook::accept(TCOD_key_t &key)
{
  return key.vk == TCODK_CHAR && key.c == 'l';
}

void CmdLook::execute()
{
  //TODO
}


}
